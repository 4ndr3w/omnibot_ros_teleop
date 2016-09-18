#include <SDL.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "joystick_drive");
  ros::NodeHandle n;
  
  SDL_Init(SDL_INIT_JOYSTICK);
  
  if ( SDL_NumJoysticks() < 1 )
  {
	  printf("No joysticks connected\n");
	  ros::shutdown();
	  return 0;
  }
  
  SDL_Joystick *js = SDL_JoystickOpen(0);
  
  if ( js == NULL )
  {
	  printf("Error opening joystick\n");
	  ros::shutdown();
	  return 0;
  }
  
  ros::Rate update(50);
  
  ros::Publisher velocityPublisher = n.advertise<geometry_msgs::Twist>("cmd_velocity", 50);
  
  while ( n.ok() ) {
	  double x = (double)SDL_JoystickGetAxis(js, 0)/32767.0;
	  double y = (double)SDL_JoystickGetAxis(js, 1)/32767.0;
	  double rotate = (double)SDL_JoystickGetAxis(js, 2)/32767.0;
	  
	  
	  geometry_msgs::Twist cmd_velocity;
	  
	  cmd_velocity.linear.x = x;
	  cmd_velocity.linear.y = y;

	  velocityPublisher.publish(cmd_velocity);
	  
	  SDL_JoystickUpdate();
	  ros::spinOnce();
	  
	  update.sleep();
  }
  
  SDL_JoystickClose(js);
  return 0;
}