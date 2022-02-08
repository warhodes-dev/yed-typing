#include <yed/plugin.h>

#define ARGS_TYPING_BUFF "*typing", (BUFF_SPECIAL)

void typing();

yed_buffer *get_or_make_buffer(char *name, int flags) {
    yed_buffer *buff;

    if ((buff = yed_get_buffer(name)) == NULL) {
        buff = yed_create_buffer(name);
    }
    buff->flags |= flags;

    return buff;
}

int yed_plugin_boot(yed_plugin *self) {
    yed_event_handler h;

    YED_PLUG_VERSION_CHECK();

    yed_plugin_set_command(self, "typing", typing);

    return 0;
}

void typing() {
    yed_buffer *buff;

    buff = get_or_make_buffer(ARGS_TYPING_BUFF);

    yed_buff_clear_no_undo(buff);

    char *target_text = "hello world";
    for (int i = 0; i < strlen(target_text); i++) {
        yed_append_to_line_no_undo(buff, 1, G(target_text[i]));
    }

    YEXE("special-buffer-prepare-focus", "*typing");
    if (ys->active_frame) {
        YEXE("buffer", "*typing");
    }
}
