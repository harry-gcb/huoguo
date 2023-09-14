aux_source_directory(${PROJECT_SOURCE_DIR}/sdp/src SDP_LIST)
add_library(sdp STATIC ${SDP_LIST})
add_library(huoguo::sdp ALIAS sdp)
target_include_directories(sdp PUBLIC ${PROJECT_SOURCE_DIR}/sdp/include)
