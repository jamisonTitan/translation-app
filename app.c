#include <stdio.h>
#include <gtk/gtk.h>

#include "api.h"

static void entry_activate_handler(GtkWidget *widget, gpointer data) {
	const gchar *user_in = gtk_editable_get_text(GTK_EDITABLE ((GtkWidget *)data));
	char user_in_as_string[sizeof(user_in)];
	snprintf(user_in_as_string, sizeof(user_in), "%s", user_in);
	printf("translated: %s \n", trans(user_in_as_string, "en", "es"));
}

static void app_activate(GApplication *app) {
	GtkWidget *win;
	GtkWidget *main_box;
	GtkWidget *entry;

	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Translator");
	gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);

	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_set_homogeneous(GTK_BOX (main_box), FALSE);
	gtk_window_set_child(GTK_WINDOW (win), main_box);

	entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY (entry), "enter text to be translated");
	g_signal_connect( entry, "activate", G_CALLBACK (entry_activate_handler), (gpointer) entry);

	gtk_box_append(GTK_BOX (main_box), entry);

	gtk_window_present (GTK_WINDOW (win));
}

int main (int argc, char** argv) {
	GtkApplication *app;
	int stat;

	app = gtk_application_new("titan.gtk.test", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
	stat = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return stat;

}

