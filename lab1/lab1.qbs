import qbs

CppApplication {
    name: "Lab 1"
    consoleApplication: true

    Group {
        name: "Source"
        prefix: "source/"
        files: "*.cpp"
    }

    Group {
        name: "Include"
        prefix: "include/"
        files: "*.h"
    }


    Group {
        fileTagsFilter: product.type
        qbs.install: true
    }

    cpp.cxxLanguageVersion: "c++14"
}
