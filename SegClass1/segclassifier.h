/** @file Image segmentation class
 * @brief : This class segments the image, assigning
 * @date : June 2017
 * @author : Martin Bueno
 * @version : 1.0
 * */

#define SEGCLASSIFIER_H

#define USE_OPENCV 1
#include <caffe/caffe.hpp>

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
//#include <chrono> //Just for time measurement. This library requires compiler and library support f$


#ifdef USE_OPENCV
using namespace caffe;  // NOLINT(build/namespaces)
using std::string;

/**
 * @brief The SegClassifier class
 */


class SegClassifier {
public:

    /**
     * @brief SegClassifier::SegClassifier
     * Classifier constructor
     * @param model_file deploy.prototxt file
     * @param trained_file trained model iwth extension *.caffemodel file
     */
    SegClassifier(const string& model_file,
               const string& trained_file);

    /**
     * @brief SegClassifier::Predict
     * Public method - conducts the actual segmentation of the image
     * @param img - Mat image to be classified
     * @param LUT_file - String with the filename of the look up table to apply to each segmentation
     * @param seg_img - the segmented Mat image. Output param
     */
    void Predict(const cv::Mat& img, string LUT_file, cv::Mat& seg_img);

private:

    /**
     * @brief SegClassifier::WrapInputLayer
     * Private method - Wrap the input layer of the network in separate cv::Mat objects
     * (one per channel). This way we save one memcpy operation and we
     * don't need to rely on cudaMemcpy2D. The last preprocessing
     * operation will write the separate channels directly to the input
     * layer.
     * @param input_channels
     */
    void WrapInputLayer(std::vector<cv::Mat>* input_channels);

    /**
     * @brief SegClassifier::Preprocess
     * Convert the input image to the input image format of the network.
     * @param img
     * @param input_channels
     */
    void Preprocess(const cv::Mat& img,
                    std::vector<cv::Mat>* input_channels);

    void Visualization(cv::Mat prediction_map, string LUT_file);

   private:
    shared_ptr<Net<float> > net_;
    cv::Size input_geometry_;
    int num_channels_;
};

#endif // SEGCLASSIFIER_H
