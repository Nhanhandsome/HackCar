# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

file(GLOB board_source "board/*.c"
					   "board/timer/*.c"
					   "board/nvc_flash/*.c"
					   "board/can_hw/*.c"
					   "board/gpio/*.c"
					   "board/uart_hw/*.c"
					   "board/ioe_hw/*.c")

idf_component_register(
    SRCS ${board_source}  
    	 main.c         # list the source files of this component
    INCLUDE_DIRS   "board"
    			   "board/ioe_hw"
    			   "board/timer"
    			   "board/nvc_flash"
    			   "board/can_hw"
    			   "board/gpio"
    			   "board/uart_hw"      # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES            # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)
