add_executable(cm02-easy main.c)
target_compile_options(cm02-easy PRIVATE /MD /Wall /Od /Ob0)

add_executable(cm02-normal main.c)
target_compile_options(cm02-normal PRIVATE /MD /Wall /O1 /Ob0)

add_executable(cm02-hard main.c)
target_compile_options(cm02-easy PRIVATE /MD /Wall /O2)
