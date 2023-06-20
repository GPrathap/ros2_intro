
#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.hpp>
#include <opencv2/highgui/highgui.hpp>

// https://github.com/ros-perception/image_transport_tutorials

class HagenCamPub : public rclcpp::Node{
  public:
    HagenCamPub(): Node("hagen_cam_pub") 
                , node_handle_(std::shared_ptr<HagenCamPub>(this, [](auto *) {}))
                , image_transport_(node_handle_)
                , pub_image_(image_transport_.advertise("/joy_hagen_camera/camera", 10)){

    }

    void camPub(){

      const int CAMERA_INDEX = 0;
      cv::VideoCapture capture(CAMERA_INDEX);
      if(not capture.isOpened())
      {
        RCLCPP_ERROR_STREAM(get_logger(), "Failed to open camera with index " << CAMERA_INDEX << "!");
        rclcpp::shutdown();
      }
      
      cv_bridge::CvImagePtr frame = std::make_shared<cv_bridge::CvImage>();
      frame->encoding = sensor_msgs::image_encodings::BGR8;
      while( rclcpp::ok() ) {
        capture >> frame->image;
        if( frame->image.empty() )
        {
          RCLCPP_ERROR( get_logger(), "Failed to capture frame!" );
          rclcpp::shutdown();
        }
        frame->header.stamp = this->now();
        pub_image_.publish(frame->toImageMsg());
        cv::waitKey(3);
        rclcpp::spin_some(this->get_node_base_interface());
      }
      capture.release();
    }

  protected:
      rclcpp::Node::SharedPtr node_handle_;
      image_transport::ImageTransport image_transport_;
      image_transport::Publisher pub_image_;
      
  private:
      float previous_speed = 0.;
      float new_speed      = 0.;

};


int main( int argc, char **argv )
{
  rclcpp::init( argc, argv);
  auto node = std::make_shared<HagenCamPub>();
  node->camPub();
  rclcpp::spin(node);
  return 0;
}

