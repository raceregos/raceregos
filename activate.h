#include <gtk/gtk.h>
#include "ad_test.c"
//#include "ad_test.h"
//extern void load_ad_panel(GtkWidget *backPanel);
static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *panel = gtk_fixed_new();

    GtkWidget *stat_panel = gtk_fixed_new();
    GtkWidget *ad_panel = gtk_fixed_new();
    GtkWidget *pkc_panel = gtk_fixed_new();
    GtkWidget *buzzer_panel = gtk_fixed_new();
    GtkWidget *bs_panel = gtk_fixed_new();

    GtkWidget *label;
    GtkWidget *notebook = gtk_notebook_new();
    GtkWidget *tab_panel = gtk_fixed_new();

    GtkWidget *cpu = gtk_label_new("CPU UTIL");
    GtkWidget *cpu_val = gtk_label_new("0%");
    GtkWidget *mem_util = gtk_label_new("MEM UTIL");
    GtkWidget *mem_util_val = gtk_label_new("0%");

    //gtk_widget_set_size_request(cpu, 100, 28);
    gtk_fixed_put(stat_panel, cpu, 10, 5);
    gtk_fixed_put(stat_panel, cpu_val, 120, 5);
    gtk_fixed_put(stat_panel, mem_util, 10, 25);
    gtk_fixed_put(stat_panel, mem_util_val, 120, 25);
    printf("step 55\n");
    if (ad_panel != NULL)
    {
        printf("success");
    }
    else
    {
        printf("s222");
    }
    //load_ad_panel(ad_panel);

    printf("step 66\n");
    // gtk_fixed_put(ad_panel, )
    //GtkWidget *page_content5 = gtk_label_new("Content 5");

    GtkWidget *label_content_1 = gtk_label_new("Status Window");
    GtkWidget *label_content_2 = gtk_label_new("Alpha Display");
    GtkWidget *label_content_3 = gtk_label_new("PK Control");
    GtkWidget *label_content_4 = gtk_label_new("Buzzer");
    GtkWidget *label_content_5 = gtk_label_new("BattleShort");

    GdkColor color;

    GdkRGBA fwidgetColor[7] = {
        {0.0, 1.0, 0.0, 1.0},
        {1.0, 1.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 1.0},
        {0.7, 0.7, 0.7, 1.0},
        {0.0, 0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {128.0, 128.0, 128.0, 0.5} // GREY
    };

    gtk_window_set_title(GTK_WINDOW(window), "TestApp");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 1000);
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &fwidgetColor[4]);

    /*UPPER LABELS*/
    label = gtk_label_new("MAINS");
    gtk_fixed_put(panel, label, 10, 10);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("FAIL");
    gtk_fixed_put(panel, label, 160, 10);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("TEMP");
    gtk_fixed_put(panel, label, 260, 10);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("BATTERY");
    gtk_fixed_put(panel, label, 360, 10);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*LABELS LEFT VERTICAL*/
    label = gtk_label_new("MAINS FEED");
    gtk_fixed_put(panel, label, 10, 60);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("UPS SOURCE");
    gtk_fixed_put(panel, label, 10, 100);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("UPS BATTERY");
    gtk_fixed_put(panel, label, 10, 140);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("UPS LOAD");
    gtk_fixed_put(panel, label, 10, 180);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("COOLING");
    gtk_fixed_put(panel, label, 10, 220);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("TEMP");
    gtk_fixed_put(panel, label, 10, 260);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("HUMIDITY");
    gtk_fixed_put(panel, label, 10, 300);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("PK");
    gtk_fixed_put(panel, label, 10, 340);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("UPS");
    gtk_fixed_put(panel, label, 200, 60);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("PRIMARY");
    gtk_fixed_put(panel, label, 200, 100);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("100%");
    gtk_fixed_put(panel, label, 200, 140);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("000");
    gtk_fixed_put(panel, label, 200, 180);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*COOLING*/
    label = gtk_label_new("000");
    gtk_fixed_put(panel, label, 200, 220);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("000");
    gtk_fixed_put(panel, label, 300, 220);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("000");
    gtk_fixed_put(panel, label, 400, 220);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("000");
    gtk_fixed_put(panel, label, 500, 220);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[2]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*TEMP*/
    label = gtk_label_new("24");
    gtk_fixed_put(panel, label, 200, 260);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("24");
    gtk_fixed_put(panel, label, 300, 260);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("24");
    gtk_fixed_put(panel, label, 400, 260);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("24");
    gtk_fixed_put(panel, label, 500, 260);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*HUMIDITY*/
    label = gtk_label_new("059");
    gtk_fixed_put(panel, label, 200, 300);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("059");
    gtk_fixed_put(panel, label, 300, 300);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("056");
    gtk_fixed_put(panel, label, 400, 300);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("055");
    gtk_fixed_put(panel, label, 500, 300);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*PK*/
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 200, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 230, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 260, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 290, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 320, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 350, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 380, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 410, 340);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 200, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 230, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 260, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 290, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 320, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 350, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 380, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);
    label = gtk_label_new("      ");
    gtk_fixed_put(panel, label, 410, 360);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    /*SUB LABELS*/
    label = gtk_label_new("10.1.15.11");
    gtk_fixed_put(panel, label, 10, 400);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[0]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("BS");
    gtk_fixed_put(panel, label, 250, 400);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[6]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("LBS");
    gtk_fixed_put(panel, label, 360, 400);
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[6]);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("ACH");
    gtk_fixed_put(panel, label, 480, 400);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    label = gtk_label_new("00:00:00");
    gtk_fixed_put(panel, label, 600, 400);
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &fwidgetColor[5]);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), stat_panel, label_content_1);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), ad_panel, label_content_2);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pkc_panel, label_content_3);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), buzzer_panel, label_content_4);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), bs_panel, label_content_5);

    //gtk_notebook_append_page(GTK_NOTEBOOK(notebook), ad_panel, label_content_2);
    gtk_widget_override_background_color(notebook, GTK_STATE_FLAG_NORMAL, &fwidgetColor[6]);

    gtk_container_set_border_width(GTK_CONTAINER(window), 2);
    gtk_fixed_put((GtkFixed *)panel, notebook, 5, 425);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), TRUE);
    gtk_container_add(GTK_CONTAINER(window), panel);
    gtk_widget_show(notebook);
    gtk_widget_show(panel);
    gtk_widget_show_all(window);
}