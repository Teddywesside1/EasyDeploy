/*
 * @Description:
 * @Author: Teddywesside 18852056629@163.com
 * @Date: 2024-12-02 19:22:45
 * @LastEditTime: 2024-12-02 19:33:03
 * @FilePath: /easy_deploy/detection_2d/detection_2d_rt_detr/src/rt_detr_factory.cpp
 */
#include "detection_2d_rt_detr/rt_detr.h"

namespace detection_2d {

struct RTDetrParams {
  std::shared_ptr<inference_core::BaseInferCoreFactory>         infer_core_factory;
  std::shared_ptr<detection_2d::BaseDetectionPreprocessFactory> preprocess_factory;
  int                                                           input_height;
  int                                                           input_width;
  int                                                           input_channel;
  int                                                           cls_number;
  std::vector<std::string>                                      input_blob_name;
  std::vector<std::string>                                      output_blob_name;
};

class Detection2DRTDetrFactory : public BaseDetection2DFactory {
public:
  Detection2DRTDetrFactory(const RTDetrParams &params) : params_(params)
  {}
  std::shared_ptr<detection_2d::BaseDetectionModel> Create() override
  {
    return CreateRTDetrDetectionModel(
        params_.infer_core_factory->Create(), params_.preprocess_factory->Create(),
        params_.input_height, params_.input_width, params_.input_channel, params_.cls_number,
        params_.input_blob_name, params_.output_blob_name);
  }

private:
  RTDetrParams params_;
};

std::shared_ptr<BaseDetection2DFactory> CreateRTDetrDetectionModelFactory(
    std::shared_ptr<inference_core::BaseInferCoreFactory>         infer_core_factory,
    std::shared_ptr<detection_2d::BaseDetectionPreprocessFactory> preprocess_factory,
    int                                                           input_height,
    int                                                           input_width,
    int                                                           input_channel,
    int                                                           cls_number,
    const std::vector<std::string>                               &input_blob_name,
    const std::vector<std::string>                               &output_blob_name)
{
  if (infer_core_factory == nullptr || preprocess_factory == nullptr)
  {
    throw std::invalid_argument("[CreateRTDetrDetectionModelFactory] Got invalid input arguments!");
  }

  RTDetrParams params;
  params.infer_core_factory  = infer_core_factory;
  params.preprocess_factory  = preprocess_factory;
  params.input_height        = input_height;
  params.input_width         = input_width;
  params.input_channel       = input_channel;
  params.cls_number          = cls_number;
  params.input_blob_name     = input_blob_name;
  params.output_blob_name    = output_blob_name;

  return std::make_shared<Detection2DRTDetrFactory>(params);
}

} // namespace detection_2d