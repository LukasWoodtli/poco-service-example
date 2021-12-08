
set(ORM_DEF_FILE ${CMAKE_CURRENT_LIST_DIR}/orm.xml)


# execute_process(
#     COMMAND xmllint --xpath "/project/class/@name" orm.xml 
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
#     OUTPUT_VARIABLE ACTIVE_RECORD_CLASSES)

# string(REPLACE " " ";" ACTIVE_RECORD_CLASSES_LIST ${ACTIVE_RECORD_CLASSES})
# list(TRANSFORM ACTIVE_RECORD_CLASSES_LIST REPLACE
#         "^name=\"([a-zA-Z0-9]+)\"$" "${CMAKE_CURRENT_BINARY_DIR}/src/\\1.cpp")


set(GENERATED_FILES_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_FILES_DIR})

set(ACTIVE_RECORD_CLASSES_LIST
    ${GENERATED_FILES_DIR}/src/Employee.cpp
    ${GENERATED_FILES_DIR}/src/Role.cpp
    ${GENERATED_FILES_DIR}/src/Address.cpp)

set_source_files_properties(${ACTIVE_RECORD_CLASSES_LIST}
                            PROPERTIES GENERATED TRUE)


add_custom_command(OUTPUT ${ACTIVE_RECORD_CLASSES_LIST}
                  COMMAND /usr/local/bin/arc ${ORM_DEF_FILE}
                  WORKING_DIRECTORY ${GENERATED_FILES_DIR}
                  DEPENDS ${ORM_DEF_FILE}
                  COMMENT "Generating active records")



add_library(persistence SHARED)
set_target_properties(persistence PROPERTIES LINKER_LANGUAGE CXX)
target_sources(persistence PRIVATE ${ACTIVE_RECORD_CLASSES_LIST})
target_include_directories(persistence PUBLIC "${GENERATED_FILES_DIR}/include")
target_link_libraries(persistence PUBLIC Poco::ActiveRecord Poco::Data Poco::Foundation)
