// Copyright 2016 Clustertech Limited. All rights reserved.
//
// Author: jackeychen (jackeychen@clustertech.com)

//go:generate g++ -c opencv.cpp
//go:generate ar q libopencv.a opencv.o

package main

// #cgo pkg-config: opencv
// #cgo LDFLAGS: -L. -lopencv -lstdc++
// #include "opencv.h"
// #include <stdlib.h>
import "C"
import "unsafe"

func main() {
	src := C.CString("lena.tiff")
	defer C.free(unsafe.Pointer(src))
	dst := C.CString("lena-demo.tiff")
	defer C.free(unsafe.Pointer(dst))
	img := unsafe.Pointer(C.loadImage(src))
	defer C.releaseImage(img)

	C.resizeImage(img, 150, 150)
	C.rotateImage(img, 30)
	C.saveImage(img, dst)
}
