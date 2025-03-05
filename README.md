# SFML_SATCollision 

## SAT Collision 공부내용(블로그 글 참조 )
- https://kwonvector.tistory.com/59
- https://kwonvector.tistory.com/60

  
## 프로젝트 생성 방법
본 SFML 프로젝트는 CMAKE 프로그램이 반드시 있어야 함(.sln 없다고 당황하지 않기)
1. 위 프로젝트를 git clone
2. cmake 프로그램 설치 설치 방법은 다음 포스트를 참조 -> https://kwonvector.tistory.com/49
3. CMakeLists.txt 를 열어서 본인이 원하는 프로젝트 이름 설정 후 저장
4. cmake 커맨드 입력(인터넷 있어야 함)
```bash
cmake ..
cmake --build .
```

## 빌드된 프로그램 조작법
- 마우스 조작
- 마우스를 클릭하면 대상 도형이 회전한다.
  
## 프로젝트에서 디버그 실행을 했는데 실행이 되지 않을 때 
우측 프로젝트 솔루션 창에서 시작 프로그램 설정이 'main' 으로 설정되어 있는지 체크할 것

## 참고한 프로젝트
https://github.com/xSnapi/SAT-Collision

