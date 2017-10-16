
#include <ros/ros.h>

#include <xpp_vis_hyq/inverse_kinematics_hyq2.h>
#include <xpp_msgs/topic_names.h>

#include <xpp_vis/urdf_visualizer.h>
#include <xpp_vis/cartesian_joint_converter.h>

using namespace xpp;
using namespace biped;

int main(int argc, char *argv[])
{
	::ros::init(argc, argv, "biped_urdf_visualizer");

	auto ik = std::make_shared<InverseKinematicsHyq2>();
  CartesianJointConverter inv_kin_converter(ik,
                                            xpp_msgs::robot_state_desired,
                                            xpp_msgs::joint_desired);

  int n_ee = biped::kMapIDToEE.size();
  int n_j  = HyqlegJointCount;
  std::vector<UrdfVisualizer::URDFName> joint_names(n_ee*n_j);
  joint_names.at(n_j*kMapIDToEE.at(L) + HAA) = "L_haa_joint";
  joint_names.at(n_j*kMapIDToEE.at(L) + HFE) = "L_hfe_joint";
  joint_names.at(n_j*kMapIDToEE.at(L) + KFE) = "L_kfe_joint";
  joint_names.at(n_j*kMapIDToEE.at(R) + HAA) = "R_haa_joint";
  joint_names.at(n_j*kMapIDToEE.at(R) + HFE) = "R_hfe_joint";
  joint_names.at(n_j*kMapIDToEE.at(R) + KFE) = "R_kfe_joint";

	std::string urdf = "biped_rviz_urdf_robot_description";
	UrdfVisualizer node(urdf, joint_names, "base", "world",
	                    xpp_msgs::joint_desired, "biped");

	::ros::spin();

	return 1;
}
