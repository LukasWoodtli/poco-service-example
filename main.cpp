
#include <Poco/ActiveRecord/Context.h>
#include <Poco/File.h>
#include "Sample/Role.h"
#include <iostream>


const constexpr auto connectionString = "data.sqlite";

int main() {
    
    if(not Poco::File(connectionString).exists())
        std::cerr << "DB file doesn't exist: " << connectionString << std::endl;

    
    Poco::Data::Session session("SQLite", connectionString);
    //Poco::Data::Session session("ODBC", "DSN=PostgreSQL");
    Poco::ActiveRecord::Context::Ptr pContext = new Poco::ActiveRecord::Context(session);

    Sample::Role::Ptr pDeveloper = new Sample::Role;
    pDeveloper->name("Developer")
        .description("Developer role");

    pDeveloper->create(pContext);
}