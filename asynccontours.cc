

struct findContours_baton_t {
  Matrix *mm;
  Persistent<Function> cb;
  vector<vector<cv::Point>> res;
  uv_work_t request;
};

void AsyncFindContoursAsync(uv_work_t *req);
void AfterAsyncFindContoursAsync(uv_work_t *req);

Handle<Value>
Matrix::FindContoursAsync(const v8::Arguments& args){
  SETUP_FUNCTION(Matrix)

  REQ_FUN_ARG(0, cb);

  findContours_baton_t *baton = new findContours_baton_t();

  baton->mm = self;
  baton->cb = Persistent<Function>::New(cb);
  baton->request.data = baton;

  uv_queue_work(uv_default_loop(), &baton->request, AsyncFindContoursAsync, (uv_after_work_cb)AfterAsyncFindContoursAsync);

  return Undefined();
}

void AsyncFindContoursAsync(uv_work_t *req) {
  findContours_baton_t *baton = static_cast<findContours_baton_t *>(req->data);

  cv::findContours(baton->mm->mat, baton->res, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
}

void AfterAsyncFindContoursAsync(uv_work_t *req) {

  HandleScope scope;
  findContours_baton_t *baton = static_cast<findContours_baton_t *>(req->data);
//  ev_unref(EV_DEFAULT_UC);
//  baton->cc->Unref();

  Local<Object> conts_to_return = Contour::constructor->GetFunction()->NewInstance();
  Contour *contours = ObjectWrap::Unwrap<Contour>(conts_to_return);
  contours->contours = baton->res;

  Local<Value> argv[2];

  argv[0] = Local<Value>::New(Null());
  argv[1] = conts_to_return;

  TryCatch try_catch;

  baton->cb->Call(Context::GetCurrent()->Global(), 2, argv);

  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }

  baton->cb.Dispose();

  delete baton;

//  return 0;
}