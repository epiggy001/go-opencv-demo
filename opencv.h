#ifdef __cplusplus
extern "C"
{
#endif
  void* loadImage(char* filename);
  void resizeImage(void* img, int width, int height);
  void rotateImage(void* img, double angle);
  void saveImage(void* img, char* filename);
  void releaseImage(void* img);
#ifdef __cplusplus
}
#endif

