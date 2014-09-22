#include "OpenCV.h"
#include "Constants.h"

#define CONST(C) inner->Set(String::NewSymbol(#C), Integer::New(C));

void
Constants::Init(Handle<Object> target) {

  Persistent<Object> inner = Persistent<Object>::New(Object::New());

  CONST(CV_8U);
  CONST(CV_8S);
  CONST(CV_16U);
  CONST(CV_16S);
  CONST(CV_32S);
  CONST(CV_32F);
  CONST(CV_64F);
  CONST(CV_USRTYPE1);

  CONST(CV_8UC1);
  CONST(CV_8UC2);
  CONST(CV_8UC3);
  CONST(CV_8UC4);

  CONST(CV_8SC1);
  CONST(CV_8SC2);
  CONST(CV_8SC3);
  CONST(CV_8SC4);

  CONST(CV_16UC1);
  CONST(CV_16UC2);
  CONST(CV_16UC3);
  CONST(CV_16UC4);

  CONST(CV_16SC1);
  CONST(CV_16SC2);
  CONST(CV_16SC3);
  CONST(CV_16SC4);

  CONST(CV_32SC1);
  CONST(CV_32SC2);
  CONST(CV_32SC3);
  CONST(CV_32SC4);

  CONST(CV_32FC1);
  CONST(CV_32FC2);
  CONST(CV_32FC3);
  CONST(CV_32FC4);

  CONST(CV_64FC1);
  CONST(CV_64FC2);
  CONST(CV_64FC3);
  CONST(CV_64FC4);

  target->Set(String::NewSymbol("Constants"), inner);
}

#undef CONST
