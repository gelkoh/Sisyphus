#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static void activate_styles() {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "styles.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

static void activate(GtkApplication *app) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_widget_set_name(window, "window");
    gtk_window_set_title(GTK_WINDOW(window), "🏺 Sisyphus – A Pomodoro Timer 🏺");
    gtk_widget_set_size_request(window, 400, 400);
    gtk_window_present(GTK_WINDOW(window));

    activate_styles();
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gelkoh.sisyphus", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
