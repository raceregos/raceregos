#include <gtk/gtk.h>

GtkWidget *lblContrast,
    *lblBrightness,
    *lblText,
    *lblInUse; //??not used
GtkWidget *rbContrast[8],
    *rbBrightness[8],
    *txtAND[4],
    *brightnessBox,
    *contrastBox;
GList *rbContGroup;
GtkWidget *ANDPanel,
    *ANDGrid,
    *ANDBrightnessGrid,
    *PKPanel;
GtkWidget *setANDTextButton,
    *setANDBrightnessButton,
    *setANDContrastButton;

//void load_ad_panel(GtkWidget *backPanel)
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *backPanel = gtk_fixed_new();
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //backPanel = gtk_fixed_new();

    gtk_window_set_default_size(GTK_WINDOW(window), 800, 1000);
    int i;
    char outStr[16];
    printf("step ad");
    gtk_container_set_border_width(GTK_CONTAINER(backPanel), 4);
    gtk_widget_set_size_request(backPanel, 600, 250);
    printf("step 1");
    ANDGrid = gtk_grid_new();
    rbContrast[0] = gtk_radio_button_new_with_label(NULL, "Lev-1");
    gtk_grid_attach(GTK_GRID(ANDGrid), rbContrast[i], 0, 0, 1, 1);
    gtk_widget_show(rbContrast[0]);
    GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbContrast[0]));
    lblContrast = gtk_label_new("Contrast");
    gtk_fixed_put((GtkFixed *)backPanel, lblContrast, 20, 10);
    for (i = 1; i < 8; i++)
    {
        sprintf(outStr, "Lev-%d", i + 1);
        group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbContrast[i - 1]));
        rbContrast[i] = gtk_radio_button_new_with_label(group, outStr);
        gtk_grid_attach(GTK_GRID(ANDGrid), rbContrast[i], i % 4, i / 4, 1, 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbContrast[i]), FALSE);
        gtk_widget_show(rbContrast[i]);
    }
    printf("step 2");
    ANDBrightnessGrid = gtk_grid_new();
    rbBrightness[0] = gtk_radio_button_new_with_label(NULL, "Lev-1");
    gtk_grid_attach(GTK_GRID(ANDBrightnessGrid), rbBrightness[0], 0, 0, 1, 1);
    gtk_widget_show(rbBrightness[0]);
    lblBrightness = gtk_label_new("Brightness");
    gtk_fixed_put((GtkFixed *)backPanel, lblBrightness, 20, 60);
    GSList *brightnessGroup = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbBrightness[0]));
    //g_signal_connect(rbBrightness[0], "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);
    gtk_widget_show(rbBrightness[0]);

    for (i = 1; i < 8; i++)
    {
        sprintf(outStr, "Lev-%d", i + 1);
        brightnessGroup = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rbBrightness[i - 1]));
        rbBrightness[i] = gtk_radio_button_new_with_label(brightnessGroup, outStr);
        gtk_grid_attach(GTK_GRID(ANDBrightnessGrid), rbBrightness[i], i % 4, i / 4, 1, 1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rbBrightness[i]), FALSE);
        //g_signal_connect(rbBrightness[i], "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);
        gtk_widget_show(rbBrightness[i]);
    }
    gtk_fixed_put((GtkFixed *)backPanel, ANDGrid, 200, 10);
    gtk_fixed_put((GtkFixed *)backPanel, ANDBrightnessGrid, 200, 60);

    lblText = gtk_label_new("Text");
    gtk_fixed_put((GtkFixed *)backPanel, lblText, 20, 110);
    for (i = 0; i < 4; i++)
    {
        txtAND[i] = gtk_entry_new();
        gtk_entry_set_text((GtkEntry *)txtAND[i], "Sample Text");
        gtk_fixed_put((GtkFixed *)backPanel, txtAND[i], 200, 110 + i * 34);
        gtk_widget_show(txtAND[i]);
    }

    setANDContrastButton = gtk_button_new_with_label("Apply Contrast");
    gtk_widget_set_size_request(setANDContrastButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDContrastButton, 480, 20);
    gtk_widget_show(setANDContrastButton);
    //g_signal_connect(setANDContrastButton, "clicked", G_CALLBACK(applyRBContrastCmd), (gpointer)NULL);

    setANDBrightnessButton = gtk_button_new_with_label("Apply Brightness");
    gtk_widget_set_size_request(setANDBrightnessButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDBrightnessButton, 480, 70);
    gtk_widget_show(setANDBrightnessButton);
    //g_signal_connect(setANDBrightnessButton, "clicked", G_CALLBACK(applyRBBrightnessCmd), (gpointer)NULL);

    setANDTextButton = gtk_button_new_with_label("Apply Text");
    gtk_widget_set_size_request(setANDTextButton, 150, 30);
    gtk_fixed_put((GtkFixed *)backPanel, setANDTextButton, 480, 160);
    gtk_widget_show(setANDTextButton);
    //g_signal_connect(setANDTextButton, "clicked", G_CALLBACK(applyTxtCmd), (gpointer)NULL);

    //gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), TRUE);
    gtk_widget_show(GTK_WIDGET(backPanel));
    //gtk_container_add(GTK_CONTAINER(window), backPanel);

    //gtk_widget_show_all(GTK_WIDGET(window));

    gtk_main();
}