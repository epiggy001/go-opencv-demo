package main
 
/*
#cgo pkg-config: opencv
#include <cv.h>
#include <highgui.h>
*/
import "C"
import "unsafe"
 
func main() {
  src := C.CString("lena_std.tif")
  defer C.free(unsafe.Pointer(src))
  img := unsafe.Pointer(C.cvLoadImage(src, C.CV_LOAD_IMAGE_COLOR))
  defer C.cvReleaseImage((**C.struct__IplImage)(unsafe.Pointer(&img)))

  greyImg := unsafe.Pointer(C.cvCreateImage(C.cvGetSize(img), 8, 1))
  C.cvConvertImage(img, greyImg, C.CV_BGR2GRAY)
  defer C.cvReleaseImage((**C.struct__IplImage)(unsafe.Pointer(&greyImg)))

  dst := C.CString("lena_grey.jpg")
  defer C.free(unsafe.Pointer(dst))

  C.cvSaveImage(dst, greyImg, nil)
}
