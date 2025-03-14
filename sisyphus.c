#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

bool is_paused = TRUE;

GtkWidget *window;
GtkWidget *center_box;
GtkWidget *timer_label_and_skip_button_box;
GtkWidget *timer_label;
GtkWidget *skip_button;
GtkWidget *play_pause_button;

static void on_timer_toggle() {
    if (is_paused) {
        gtk_button_set_label(GTK_BUTTON(play_pause_button), "PAUSE");
        is_paused = FALSE;
    } else {
        gtk_button_set_label(GTK_BUTTON(play_pause_button), "PLAY");
        is_paused = TRUE;
    }
}

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
    // Create widgets
    window = gtk_application_window_new(app);
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    timer_label_and_skip_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    timer_label = gtk_label_new("25:00");
    skip_button = gtk_button_new_with_label("x");
    play_pause_button = gtk_button_new_with_label("PLAY");

    // Set widget options
    gtk_window_set_title(GTK_WINDOW(window), "🏺 Sisyphus – A Pomodoro Timer 🏺");
    gtk_widget_set_size_request(window, 400, 400);
    gtk_widget_set_hexpand(center_box, TRUE);
    gtk_widget_set_vexpand(center_box, TRUE);
    gtk_widget_set_halign(center_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(center_box, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(skip_button, GTK_ALIGN_END);
    gtk_widget_set_valign(skip_button, GTK_ALIGN_START);
    gtk_widget_set_halign(play_pause_button, GTK_ALIGN_CENTER);

    // Add signals
    g_signal_connect(play_pause_button, "clicked", G_CALLBACK(on_timer_toggle), NULL);

    // Add classes to widgets for CSS styling
    gtk_widget_add_css_class(skip_button, "button");
    gtk_widget_add_css_class(play_pause_button, "button");

    // Add specific names to widgets for CSS styling
    gtk_widget_set_name(window, "window");
    gtk_widget_set_name(center_box, "center-box");
    gtk_widget_set_name(timer_label, "timer-label");
    gtk_widget_set_name(skip_button, "skip-button");
    gtk_widget_set_name(play_pause_button, "play-pause-button");

    // Assemble the UI
    gtk_window_set_child(GTK_WINDOW(window), center_box);
    gtk_box_append(GTK_BOX(center_box), timer_label_and_skip_button_box);
    gtk_box_append(GTK_BOX(timer_label_and_skip_button_box), timer_label);
    gtk_box_append(GTK_BOX(timer_label_and_skip_button_box), skip_button);
    gtk_box_append(GTK_BOX(center_box), play_pause_button);

    // Present the window and activate the styles
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
