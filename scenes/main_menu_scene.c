#include "main_menu_scene.h"

static void main_menu_dialog_callback(void* context) {
    YRM100* app = context;
    DialogEx* dialog = app->gui_m->DialogView;
    MainMenuResult result = dialog_ex_get_result(dialog);

    switch(result) {
    case MainMenuResultScan:
        scene_manager_next_scene(app->gui_m->scene_manager, ScanOptionsScene_Index);
        break;
    case MainMenuResultWrite:
        scene_manager_next_scene(app->gui_m->scene_manager, WriteTagScene_Index);
        break;
    case MainMenuResultLoad:
        scene_manager_next_scene(app->gui_m->scene_manager, LoadTagScene_Index);
        break;
    case MainMenuResultSave:
        scene_manager_next_scene(app->gui_m->scene_manager, SaveTagScene_Index);
        break;
    }
}

void main_menu_scene_on_enter(void* context) {
    YRM100* app = context;
    DialogEx* dialog = app->gui_m->DialogView;

    dialog_ex_reset(dialog);
    dialog_ex_set_header(dialog, "YRM100 Reader", 64, 2, AlignCenter, AlignTop);
    dialog_ex_set_text(dialog, "Choose action:", 64, 32, AlignCenter, AlignCenter);
    dialog_ex_set_left_button_text(dialog, "Scan");
    dialog_ex_set_right_button_text(dialog, "Write");
    dialog_ex_set_center_button_text(dialog, app->tag_data_loaded ? "Save" : "Load");
    dialog_ex_set_result_callback(dialog, main_menu_dialog_callback);
    dialog_ex_set_context(dialog, app);

    view_dispatcher_switch_to_view(app->gui_m->view_dispatcher, DialogView_Index);
}

bool main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void main_menu_scene_on_exit(void* context) {
    YRM100* app = context;
    dialog_ex_reset(app->gui_m->DialogView);
}
