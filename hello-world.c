#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct {
    GtkWidget *caller;
    gchar *message;
} callback_io;

static void read_callback(GObject *source, GAsyncResult *res, gpointer data) {
    callback_io *out = data;

    g_print("%s", out->message);
    gtk_button_set_label((GtkButton *)out->caller, out->message);
}

static void notif_display(GtkWidget *widget, gpointer data) {
    GError *error = NULL;
    GInputStream *output;
    GSubprocess *process;
    gchar out[30];
    callback_io *pass;

    pass = malloc(sizeof(callback_io));
    // HELL YEAH THIS WORKS BABEYYYYYYYYYYYY
    // Thank you Beveridge
    // https://stackoverflow.com/questions/66430261/how-do-i-call-a-program-from-a-gtk-program-and-analyze-the-programs-output
    process = g_subprocess_new(G_SUBPROCESS_FLAGS_STDOUT_PIPE, &error,

                               "notify-send", "-A", "Hello='Press me'",
                               "Testing", "-t", "10000", NULL);

    pass->caller = widget;
    pass->message = out;
    output = g_subprocess_get_stdout_pipe(process);
    // Modified this part so it was asynchronous, will probably be useful as
    // reference for running
    g_input_stream_read_async(output, out, 30, 2, NULL, read_callback, pass);
}

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Testing\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    // gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    grid = gtk_grid_new();
    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(notif_display), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Testing");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {

    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
