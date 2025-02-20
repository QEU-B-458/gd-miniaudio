#ifndef GDMINIAUDIO_REGISTER_TYPES
#define GDMINIAUDIO_REGISTER_TYPES
// #include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <miniaudio_input_device.h>
#include <gdminiaduio_remote_stream_data_source.h>
#include <gdminiaudio.h>

using namespace godot;

static GDMiniaudio* miniaudio_server;

void initialize(ModuleInitializationLevel p_level) {

    if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
        ClassDB::register_class<GDMiniaudioRemoteStreamDataSource>();
        ClassDB::register_class<MiniaudioInputDevice>();
        ClassDB::register_class<MiniaudioSound>();
        ClassDB::register_class<GDMiniaudio>();
        miniaudio_server = memnew(GDMiniaudio);
        // miniaudio_server->initialize_engine();
        // miniaudio_server->start_engine();
        godot::Engine* engine{ godot::Engine::get_singleton()};
        engine->register_singleton(StringName("MiniaudioServer"), miniaudio_server);
    }
}

void uninitialize(ModuleInitializationLevel p_level) {

    if (p_level==MODULE_INITIALIZATION_LEVEL_SCENE) {
        if (miniaudio_server){
            memdelete(miniaudio_server);
        }
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize);
    init_obj.register_terminator(uninitialize);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_CORE);

    return init_obj.init();
}
}
#endif // GDMINIAUDIO_REGISTER_TYPES