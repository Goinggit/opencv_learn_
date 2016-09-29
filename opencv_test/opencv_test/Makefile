Target	= opencv
CC = g++
ARRU = ar -ru
SRC_CPP=addWeighted.cpp boundingRect.cpp calcBackProject.cpp calcHist.cpp canny.cpp compareHist.cpp \
convexHull.cpp cornerEigenValsAndVecs.cpp cornerSubPix.cpp DFT.cpp distanceTransform.cpp draw.cpp \
emapping.cpp EqualizeHist.cpp face_CascadeClassifier.cpp feature_describe.cpp FeatureDetector.cpp \
FeatureDetector.cpp findHomography.cpp first_step.cpp FLANN.cpp floodfill.cpp harris.cpp \
HoughCircles.cpp HoughLines.cpp Laplace.cpp light.cpp mask.cpp matchTemplate.cpp moments.cpp \
pointPolygonTest.cpp pyramid.cpp rand.cpp rotateRect.cpp Shi-Tomasi.cpp  smooth.cpp sobel.cpp \
SVM.cpp threshold.cpp trackbar.cpp video.cpp warpAffine.cpp xml.cpp
LIB_FLAG= -lopencv_core  -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_objdetect \
-lopencv_features2d -lopencv_ml -lopencv_flann -lopencv_nonfree -lopencv_calib3d -lopencv_legacy \
-lopencv_ts -lopencv_contrib -lopencv_ocl -lopencv_gpu -lopencv_photo -lopencv_stitching \
-lopencv_superres -lopencv_videostab

OBJ_CPP = $(SRC_CPP:.cpp=.o)
CPP_FLAGS =  -c -g -Wall
.SUFFIXES: .o .cpp
.cpp.o:
	$(CC)  $(CPP_FLAGS) $< -o $@
all: $(Target)

$(Target):$(OBJ_CPP)
	$(CC) -g $(LIB_FLAG) -o $@ $^ $(MODULE_LIB)
clean:
	rm $(Target) *.o