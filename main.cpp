#include <gtkmm.h>
#include <cmath>
#include <iostream>
#include <iomanip>

#define PI 3.141592653589793

class win {
	private:
		// Create the builder of the glade file
		Glib::RefPtr<Gtk::Builder> builder;

		// Declare widgets from the galde file that we want to interact with
		Gtk::Window* w = 0;
		Gtk::SpinButton* px = 0;
		Gtk::SpinButton* pz = 0;
		Gtk::SpinButton* dx1 = 0;
		Gtk::SpinButton* dz1 = 0;
		Gtk::Button* btn = 0;
		Gtk::Label* result = 0;

		// A simple function to close the window
		void close();
	public:
		// The kit is directly here
		win(Gtk::Main kit);
};

void win::close() {
	if (w)
		w->hide();
}

win::win(Gtk::Main kit) {
	// Init the builder and connect the widget
	builder = Gtk::Builder::create_from_file("main.glade");
	builder->get_widget("window", w);
	
	// Runs the window because now, the widget from the glade file is linked to w (our window)
	if (w) {
		// Connect the widgets from the glade file to our widgets
		builder->get_widget("pxcoo1", px);
		builder->get_widget("pzcoo1", pz);
		builder->get_widget("dxcoo1", dx1);
		builder->get_widget("dzcoo1", dz1);
		builder->get_widget("estimate", btn);
		builder->get_widget("result", result);
		// We connect the signal clicked() of the button to a lambda function. Idk why this function needs the [=] but hey, it works
		if (btn) {
			btn->signal_clicked().connect([=](){
				// Here, we create references to make the computations more simple (for me)
				float x = px->get_value();
				float z = pz->get_value();
				float dx = dx1->get_value();
				float dz = dz1->get_value();

				// First, compute the distance
				int r = round(hypot(dx-x, dz-z));
				// Then, compute the angle
				float f = atan((dx-x)/(dz-z))*(180/PI);
				float df = abs(f);
				// Adjust the values to Minecraft
				if (dx < x && dz < z) {
					df = 180-df;
				}
				if (dx > x && dz < z) {
					df = -180+df;
				}
				if (dx > x && dz > z) {
					df = 0-df;
				}

				std::ostringstream str;
				str.precision(1);
				str << std::fixed;
				str << "To reach this destination, you'll have to:\n";
				str << "1. Orient yourself by ";
				str << round(df*10)/10;
				str << " degrees\n";
				str << "2. Travel ";
				str << r;
				str << " blocks.";
				result->set_text(str.str());
				std::cout << round(df*10)/10 << " " << r << std::endl;
			});
		}
		// Finally, run the window
		kit.run(*w);
	}
}

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
	win w(kit);
	return 0;
}
