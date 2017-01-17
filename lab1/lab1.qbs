import qbs

CppApplication {
    name: "Lab 1"
    consoleApplication: true

    Group {
        name: "Source"
        prefix: "source/"
        files: "*.cpp"
        cpp.includePaths: ["include"]
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

    cpp.cxxLanguageVersion: "c++1z"
}
