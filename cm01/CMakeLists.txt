add_executable(cm01-easy main.c)
target_compile_options(cm01-easy PRIVATE /MD /Wall /Od /Ob0)

add_executable(cm01-normal main.c)
target_compile_options(cm01-normal PRIVATE /MD /Wall /O1 /Ob0)

add_executable(cm01-hard main.c)
target_compile_options(cm01-easy PRIVATE /MD /Wall /O2)
