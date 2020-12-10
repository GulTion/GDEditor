// Import GTK library for Making of Window and Widgets
#include <gtk/gtk.h>
// Import Webkit
#include <webkit2/webkit2.h>



//Declare the Pointer for Webkit_webview
typedef struct {
    GtkWidget *w_webkit_webview;
} app_widgets;


//Main
int main(int argc, char *argv[])
{
    // Pointer to Locate the Location of the Render File
    FILE * f = fopen("render","r");

    // Data of Render File
    char * buffer = 0;

    //Size of File (req: We need Size for Init in Malloc)
    long length;

    // if File found then Do
    if(f){
        // for Send f pointer to the end Byte of the Render File
        fseek(f,0,SEEK_END);

        // ftell (position of f pointer)
        length = ftell(f);

        // Reset the Location of the f pointer
        fseek(f,0,SEEK_SET);

        // Take the Heap length size
        buffer = malloc(length);

        // if Heap get SUccessfully
        if(buffer){

            // Read from and Write to the Buffer byte to byte
            fread(buffer, 1,length,f);
        }

        // if Work in Done then Close the Render file
        fclose(f);

    }

    //  To initialize the Window pointer (to hold location of the wiget who are going to render in the Window)
    GtkWidget *window;

    // design the window layout as per in .glade file 
    GtkBuilder *builder;

    //g_slice_new for allocation for the size of the 
    app_widgets *widgets = g_slice_new(app_widgets);

    // Turn on Process
    gtk_init(&argc, &argv);



    webkit_web_view_get_type();
    webkit_settings_get_type();


    // Get file and Get ready to build from .glade
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    // Get window objec from the layout
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    // Get Webkit object form the layout
    widgets->w_webkit_webview  = GTK_WIDGET(gtk_builder_get_object(builder, "webkit_webview"));

    // load Render data form Heap (buffer pointer)
    webkit_web_view_load_html(WEBKIT_WEB_VIEW(widgets->w_webkit_webview),buffer,"");
    
    // to active all signals from the builder
    // *to close the GDEDITOR
    gtk_builder_connect_signals(builder, NULL);



    // who point to location of builder unref them
    g_object_unref(builder);

    // to SHow the all Widget inside the WIndow object or Widget
    gtk_widget_show_all(window);
    
    // free all the point
    g_slice_free(app_widgets, widgets);


    // Window will apprear Suddenly afte the gtk_main() call
    gtk_main();

    return 0;
}

// Signal for closing the Window
void on_window_destroy(){
    gtk_main_quit();
}

