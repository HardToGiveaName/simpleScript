CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

PROJECT(simple_script)

SET(CMAKE_C_STANDARD 99)

SET (SRC
  ${PROJECT_SOURCE_DIR}/craft/main.c
  ${PROJECT_SOURCE_DIR}/craft/token.h
  ${PROJECT_SOURCE_DIR}/craft/token.c
  ${PROJECT_SOURCE_DIR}/craft/ast.h
  ${PROJECT_SOURCE_DIR}/craft/ast.c
  ${PROJECT_SOURCE_DIR}/craft/variable.h
  ${PROJECT_SOURCE_DIR}/craft/variable.c
  ${PROJECT_SOURCE_DIR}/craft/lexer.h
  ${PROJECT_SOURCE_DIR}/craft/lexer.c
  ${PROJECT_SOURCE_DIR}/craft/parser.h
  ${PROJECT_SOURCE_DIR}/craft/parser.c
  ${PROJECT_SOURCE_DIR}/craft/simpleScript.h
  ${PROJECT_SOURCE_DIR}/craft/simpleScript.c
)

ADD_EXECUTABLE (simple_script ${SRC})