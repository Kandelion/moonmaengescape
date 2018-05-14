# 문맹탈출 - Capstone1 Project  
* 이 branch는 현재 google cloud translation을 구현중에 있습니다.
> # Dependency
> 언어 : CPP  
> 사용 라이브러리 : Curl, rapidJSON  
>  
> # Usage
> * __Class name__
>   * `translator`  
> * __Visible function__ 
>   * const char* `translate` (const char *)
>
> ```
> translator TR;    //define class
> char* source;     //set your own text at here
> char* result;     //results will be stored here.
> 
> result = TR.translate ((const char*)source);
>
> if(result == NULL)
>   //ERROR
> else
>   //TODO
> ```
* 번역 부분 개발은 종료되었습니다.