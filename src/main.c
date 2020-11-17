#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

typedef struct {
    GtkWidget *w_webkit_webview;
} app_widgets;


int main(int argc, char *argv[])
{
   
    FILE * f = fopen("render.html","r");
    char * buffer = 0;
    long length;

    if(f){
        fseek(f,0,SEEK_END);
        length = ftell(f);
        fseek(f,0,SEEK_SET);
        buffer = malloc(length);
        if(buffer){
            fread(buffer, 1,length,f);
        }
        fclose(f);

    }
    GtkWidget *window;
    GtkBuilder *builder;
    app_widgets *widgets = g_slice_new(app_widgets);
    gtk_init(&argc, &argv);

    webkit_web_view_get_type();
     webkit_settings_get_type();


    builder = gtk_builder_new_from_file("glade/window_main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    widgets->w_webkit_webview  = GTK_WIDGET(gtk_builder_get_object(builder, "webkit_webview"));


    webkit_web_view_load_html(WEBKIT_WEB_VIEW(widgets->w_webkit_webview), buffer,"");
    
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show_all(window);
    g_slice_free(app_widgets, widgets);

    gtk_main();

    return 0;
}

void on_window_destroy(){
    gtk_main_quit();
}

