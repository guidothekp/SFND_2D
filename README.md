# MP.0 Mid-Term Report                                                              
I added some files and modified the return types of the provided functions so       
that the added can be gleaned for post processing. Further, I used the original  
file `MTPCS.cpp` for all the work.                                                    
                                                                                    
The original file is `MidTermProject_Camera_Student.cpp`.                             

In addition, I created a folder named `reports` where the results for problems 7,  
8, and 9 are output.                                                                
                                                                                    
The results are generated every time the program mtpcs is run. The results are   
stored in the `results` folder.                                                       
                                                                                    
The graphs are in the `.xlsx` files in the reports folder.                            
                                                                                    
## MP.1 Data Buffer Optimization
###### Implement a vector for dataBuffer objects whose size does not exceed a limit (e.g. 2 elements). This can be achieved by pushing in new elements on one end and removing elements on the other end.

Added the following lines of code so that we erase the previous contents and        
keep only fixed number (`dataBufferSize`) entries at any point.                       
&nbsp;
```
                if (dataBuffer.size() == dataBufferSize) {                          
                    dataBuffer.erase(dataBuffer.begin());                           
                 }                                                                  
                dataBuffer.push_back(frame);                                        
```                                                                                    
## MP.2 Keypoint Detection                                                          
###### Implement detectors HARRIS, FAST, BRISK, ORB, AKAZE, and SIFT and make them selectable by setting a string accordingly.
&nbsp;                                                                                  
Made the required modifications in the files provided.                              
                                                                                    
## MP.3 Keypoint Removal                                                            
###### Remove all keypoints outside of a pre-defined rectangle and only use the keypoints within the rectangle for further processing.
&nbsp;
```                                
        if (bFocusOnVehicle)
        {                                                                           
            std::vector<cv::KeyPoint> filtered;      
            for (const auto & keyPoint : keypoints) {                            
                if (vehicleRect.contains(keyPoint.pt)) filtered.push_back(keyPoint);
            }                                                                    
            keypoints = filtered;                                                
            metrics.carKeyPoints.push_back(keypoints.size());                    
            if (LOG) std::cout << "keypoint count after vehicle filtering: " << keypoints.size() << std::endl;
        }                                                                     
```                                                                        
## MP.4 Keypoint Descriptors                                                     
###### Implement descriptors BRIEF, ORB, FREAK, AKAZE and SIFT and make them selectable by setting a string accordingly.
&nbsp;                                                                                
Made the required modifications in the files provided.                           
                                                                                 
## MP.5 Descriptor Matching                                                      
##### Implement FLANN matching as well as k-nearest neighbor selection. Both methods must be selectable using the respective strings in the main function.
&nbsp;
Made the required modifications in the files provided.                           
                                                                                 
## MP.6 Descriptor Distance Ratio                                                
###### Use the K-Nearest-Neighbor matching to implement the descriptor distance ratio test, which looks at the ratio of best vs. second-best match to decide whether to keep an associated pair of keypoints.
&nbsp;
Made the required modifications in the files provided.                           
                                                                                 
## MP.7 Performance Evaluation 1                                                 
###### Count the number of keypoints on the preceding vehicle for all 10 images and take note of the distribution of their neighborhood size. Do this for all the detectors you have implemented.
&nbsp;                                                                           
I added up the number of keypoints per each image and noted the number of        
keypoints in the preceding vehicle and those outside. Then I averaged them for   
each run of detector. Then I noted the ratios of the means for each detector.    
The results of this are shown in `mp7.xslx` in the reports folder.                 
                                                                                 
## MP.8 Performance Evaluation 2                                                 
###### Count the number of matched keypoints for all 10 images using all possible combinations of detectors and descriptors. In the matching step, the BF approach is used with the descriptor distance ratio set to 0.8.                         
&nbsp;
The results are tabulated in `mp8.xslx` under the reports folder.                         
                                                                                 
## MP.9 Performance Evaluation 3                                                 
###### Log the time it takes for keypoint detection and descriptor extraction. The results must be entered into a spreadsheet and based on this data, the TOP3 detector / descriptor combinations must be recommended as the best choice for our purpose of detecting keypoints on vehicles.
&nbsp;                                                                                
As shown in `mp9.xslx` in the reports folder, the top three (detector,             
descriptor) pairs are `(FAST, BRISK)`, `(FAST, BRIEF)`, and `(FAST, ORB)`.             
                                                                   
The detection is where most of the time is spent. The descriptor business is relatively fast. Since the detection time is least for FAST, it is no surprise that FAST shows up in the top three detector/descriptors.               
