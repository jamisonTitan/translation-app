#include <stdio.h>
#include <gtk/gtk.h>

#include "api.h"
#include "langs.h"
#include "lang_utils.h"

char source_lang[8] = "en";
char target_lang[8] = "es";
char* langs_strings[110];

static void source_lang_handler(GtkDropDown *widget, gpointer data) {
	const gchar *selected_str = gtk_string_object_get_string(GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(widget)));
	snprintf(source_lang, sizeof(selected_str), "%s", selected_str);
}

static void target_lang_handler(GtkDropDown *widget, gpointer data) {
	const gchar *selected_str = gtk_string_object_get_string(GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(widget)));
	snprintf(target_lang, sizeof(selected_str), "%s", selected_str);
}

static void trans_handler(GtkWidget *widget, gpointer data) {
	const gchar *user_in = gtk_editable_get_text(GTK_EDITABLE ((GtkWidget *)data));
	char user_in_as_string[sizeof(user_in)];
	snprintf(user_in_as_string, sizeof(user_in), "%s", user_in);

	printf("translated from %s to %s: %s \n", source_lang, target_lang, trans(user_in_as_string, "en", "es"));
}

static void app_activate(GApplication *app) {
	//const char** langs_strings_cpy;

	GtkWidget *win;
	GtkWidget *main_box;
	GtkWidget *text_in_box;
	GtkWidget *entry;
	GtkWidget *trans_btn;
	GtkWidget *langs_in_box;
	GtkWidget *source_lang_dropdown;
	GtkWidget *target_lang_dropdown;

	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Translator");
	gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);

	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_set_homogeneous(GTK_BOX (main_box), FALSE);
	gtk_window_set_child(GTK_WINDOW (win), main_box);

	text_in_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
	gtk_box_set_homogeneous(GTK_BOX (text_in_box), FALSE);

	langs_in_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	source_lang_dropdown = gtk_drop_down_new_from_strings((const char**) langs_strings);
	target_lang_dropdown = gtk_drop_down_new_from_strings((const char**) langs_strings);

	entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY (entry), "enter text to be translated");

	trans_btn = gtk_button_new_with_label("Go!");

	g_signal_connect(trans_btn, "clicked", G_CALLBACK (trans_handler), (gpointer) entry);
	g_signal_connect(entry, "activate", G_CALLBACK (trans_handler), (gpointer) entry);
	g_signal_connect(source_lang_dropdown, "notify",  G_CALLBACK (source_lang_handler), (gpointer) source_lang_dropdown);

	gtk_box_append(GTK_BOX (text_in_box), entry);
	gtk_box_append(GTK_BOX (text_in_box), trans_btn);
	gtk_box_append(GTK_BOX (main_box), text_in_box);

	gtk_box_append(GTK_BOX (langs_in_box), source_lang_dropdown);
	gtk_box_append(GTK_BOX (langs_in_box), target_lang_dropdown);
	gtk_box_append(GTK_BOX (main_box), langs_in_box);

	gtk_window_present (GTK_WINDOW (win));
}

int main (int argc, char** argv) {
	GtkApplication *app;
	int stat;

	init_langs_strings(langs_strings);

	printf("afsssss %s\n", langs_strings[0]);

	app = gtk_application_new("titan.gtk.test", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
	stat = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return stat;

}

