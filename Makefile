CXX = g++
CXXFLAGS = -I/home/ariel/opencv-install/include/opencv4
LDFLAGS = -L/home/ariel/opencv-install/lib
LDLIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

revelar: revelar_codigo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

run: revelar
	LD_LIBRARY_PATH=/home/ariel/opencv-install/lib ./revelar

clean:
	rm -f revelar
