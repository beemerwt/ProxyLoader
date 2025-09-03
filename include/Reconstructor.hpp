#pragma once
#include <Windows.h>

struct Il2CppImage {
    const char* name;
    const char* nameNoExt;
    const char* assemblyName;
    void* typeStart;
    void* typeEnd;
};

struct Il2CppClass {
    Il2CppImage* image;
    const char* name;
    const char* namespaze;
    const char* assemblyName;
    const char* imageName;
    void* fields;
};

void DumpAllClasses() {
    Il2CppDomain* domain = il2cpp_domain_get();
    size_t count;
    Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &count);

    for (size_t i = 0; i < count; ++i) {
        Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);
        const size_t classCount = il2cpp_image_get_class_count(image);

        for (size_t j = 0; j < classCount; ++j) {
            Il2CppClass* klass = il2cpp_image_get_class(image, j);

            const char* ns = il2cpp_class_get_namespace(klass);
            const char* name = il2cpp_class_get_name(klass);
            printf("class %s.%s {\n", ns, name);

            void* fieldIter = nullptr;
            while (const FieldInfo* field = il2cpp_class_get_fields(klass, &fieldIter)) {
                const char* fieldName = field->name;
                Il2CppType* fieldType = field->type;
                const char* fieldTypeName = il2cpp_type_get_name(fieldType);
                printf("    %s %s;\n", fieldTypeName, fieldName);
            }

            printf("};\n\n");
        }
    }
}
