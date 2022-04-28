cmake_minimum_required(VERSION 3.23)

project(Factolog)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -ggdb -std=c++03")

include_directories(${Factolog_SOURCE_DIR}/include)

add_executable(factolog
                src/argumentParser.cpp
                src/arithmeticCombinator.cpp
                src/assignment.cpp
                src/asyncExpression.cpp
                src/asyncModule.cpp
                src/base64.cpp
                src/binaryExpression.cpp
                src/blueprint.cpp
                src/color.cpp
                src/combinator.cpp
                src/compilationUnit.cpp
                src/compiler.cpp
                src/constantCombinator.cpp
                src/entity.cpp
                src/exceptions.cpp
                src/expression.cpp
                src/factolog.cpp
                src/factor.cpp
                src/identifier.cpp
                src/lexer.cpp
                src/linkingUnit.cpp
                src/memtrace.cpp
                src/moduleConnection.cpp
                src/number.cpp
                src/parameter.cpp
                src/parameterList.cpp
                src/parameterListDeclaration.cpp
                src/pole.cpp
                src/position.cpp
                src/term.cpp
                src/token.cpp
                src/translator.cpp
                src/unaryExpression.cpp
                src/value.cpp
                src/valueExpression.cpp
                src/variableDeclaration.cpp
            )

install(TARGETS factolog DESTINATION bin)