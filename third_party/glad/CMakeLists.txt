ADD_LIBRARY( glad STATIC
    ./src/glad.c
    ./include/glad/glad.h
)

TARGET_INCLUDE_DIRECTORIES( glad PUBLIC
    ./include
)

set_target_properties( glad PROPERTIES 
    LINKER_LANGUAGE C
)