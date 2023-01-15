import java.awt.*;
import java.net.URL;
import java.applet.*;

// JpegAnim, copyright 1998 by Boutell.Com, Inc. Permission
// granted to use this applet on any web site.

public class JpegAnim extends Applet implements Runnable
{
	// How many images
	int imagesTotal;
	// The images to animate
	Image images[];
	// The delay in milliseconds for each
	int delays[];
	// The current frame image
	Image frame;
	// Thread that updates the count
	Thread mainThread;
	// Offscreen image where we'll sketch everything first
	// before copying it smoothly to the real screen
	Image offscreen;
	// True when we're not on the screen and shouldn't do much
	boolean paused;
	// Number of repetitions. -1 means we cycle forever.
	int cycles = -1;
	// Current repetition. 
	int cycle = 0;
	// Start of applet's execution...
	public void init() 
	{
		// Just make our own thread, where we can do our
		// own work without holding up the browser
		// (see the run method below).
		mainThread = new Thread(this);
		mainThread.start();
	}
	public void run()
	{
		int i = 0;
		while (true) {
			String s = "image" + Integer.toString(i + 1);
			if (getParameter(s) != null) {
				imagesTotal++;
			} else {
				break;
			}
			i++;
		}
		images = new Image[imagesTotal];
		delays = new int[imagesTotal];
		// Set a pleasant color.
		setBackground(Color.white);
		// Use the directory we came from to look
		// for images in.
		URL base = getCodeBase();
		MediaTracker mt = new MediaTracker(this);
		if (getParameter("cycles") != null) {
			cycles = Integer.parseInt(getParameter("cycles"));
		} else {
			cycles = -1;
		}
		try {
			for (i = 0; (i < imagesTotal); i++) {
				String s = "image" + Integer.toString(i + 1);
				String d = "delay" + Integer.toString(i + 1);
				images[i] = getImage(base, getParameter(s));
				mt.addImage(images[i], 0);
				if (getParameter(d) != null) {
					delays[i] = Integer.parseInt(
						getParameter(d));
				} else {
					delays[i] = 1000;
				}
			}
			// Wait for all of the images to load.
			// It looks less distracting that way,
			// and we know how big everything is.
			mt.waitForAll();
		} catch (Exception e) {
			// A simple, polite exception handler. "Darn."
			System.out.println("Oh Dear");	
			System.out.println();
			System.out.println("Sorry, some or all of the " +
				"pictures didn't load.");
		}
		// Which choice to use, to start with...
		frame = images[0];
		// Make the offscreen scratchpad image
		offscreen = createImage(bounds().width, bounds().height);
		// We're not paused
		paused = false;
	
		// MAIN BODY

		for (cycle = 0; ((cycles == -1) || (cycle < cycles)); 
			cycle++) 
		{
			int count;
			// Move through the steps
			for (count = 0; (count < imagesTotal); count++) {
				// Do stuff
				step(count);
				// Don't draw if we're paused. It's hard
				// on the CPU.
				if (!paused) {
					// Redraw
					draw();
				}
				// Sleep for a while
				rest(count);	
			}
		}	
	}
	void step(int count)
	{
		frame = images[count];
	}
	void rest(int count)
	{
		// Wait for the designated time.
		try {
			mainThread.sleep(delays[count]);
		} catch (Exception e) {
		}
	}
	public void paint(Graphics g)
	{
		// Careful, don't draw before we have a frame.
		if (frame == null) {
			return;
		}
		// Needed from time to time when the browser
		// asks for a repaint.
		g.drawImage(frame, 0, 0, this);
	}
	void draw()
	{
		// Clear our work area
		Graphics g = offscreen.getGraphics();
		g.setColor(Color.white);
		g.fillRect(0, 0, bounds().width, bounds().height);
		// Draw stuff 
		g.drawImage(frame, 0, 0, this);
		// Give up the graphics context we used
		g.dispose();
		// And now copy it to the real applet all at once boomp!
		g = getGraphics();
		g.drawImage(offscreen, 0, 0, this);
		g.dispose();
	}

	// MESSAGES FROM MOM: Do What The Browser Says

	public void start() {
		// A new lease on life. But don't jump to the
		// first frame, because of possible stuttering.
		cycle = -1;
		paused = false;
	}
	public void stop() {
		paused = true;
	}
	public void destroy() {
		mainThread.stop();
		mainThread = null;
	}
}

