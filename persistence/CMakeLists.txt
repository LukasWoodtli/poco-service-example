
set(ORM_DEF_FILE ${CMAKE_CURRENT_LIST_DIR}/orm.xml)



execute_process(
    COMMAND xmllint --xpath "/project/class/@name" orm.xml 
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE ACTIVE_RECORD_CLASSES)

string(REPLACE " " ";" ACTIVE_RECORD_CLASSES_LIST ${ACTIVE_RECORD_CLASSES})
list(TRANSFORM ACTIVE_RECORD_CLASSES_LIST REPLACE
        "^name=\"([a-zA-Z0-9]+)\"$" "${CMAKE_CURRENT_BINARY_DIR}/src/\\1.cpp")



add_custom_command(OUTPUT ${ACTIVE_RECORD_CLASSES_LIST}
                  COMMAND arc ${ORM_DEF_FILE}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  DEPENDS ${ORM_DEF_FILE}
                  COMMENT "Generating active records")



add_library(persistence SHARED)
target_sources(persistence PRIVATE ${ACTIVE_RECORD_CLASSES_LIST})
target_include_directories(persistence PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(persistence PUBLIC PocoActiveRecord PocoData PocoFoundation)
