/* libseahorse.vapi generated by valac, do not modify. */

[CCode (cprefix = "Seahorse", lower_case_cprefix = "seahorse_")]
namespace Seahorse {
	[CCode (cprefix = "SEAHORSE_LOCATION_", cheader_filename = "seahorse-types.h")]
	public enum Location {
		INVALID,
		MISSING,
		SEARCHING,
		REMOTE,
		LOCAL
	}
	[CCode (cprefix = "SEAHORSE_USAGE_", cheader_filename = "seahorse-types.h")]
	public enum Usage {
		NONE,
		SYMMETRIC_KEY,
		PUBLIC_KEY,
		PRIVATE_KEY,
		CREDENTIALS,
		IDENTITY,
		OTHER
	}
	[CCode (cheader_filename = "seahorse-commands.h")]
	public abstract class Commands : GLib.Object {
		public abstract void show_properties (Seahorse.Object obj);
		public abstract Seahorse.Operation? delete_objects (GLib.List<Seahorse.Object> obj);
		public Seahorse.View view { get; construct; }
		public abstract GLib.Quark ktype { get; }
		public abstract Gtk.ActionGroup command_actions { get; }
		public abstract string ui_definition { get; }
	}
	[CCode (cheader_filename = "seahorse-generator.h")]
	public abstract class Generator : GLib.Object {
		public abstract Gtk.ActionGroup actions { get; }
	}
	[CCode (cheader_filename = "seahorse-object.h")]
	public abstract class Object : GLib.Object {

 	       	[CCode (cprefix = "SEAHORSE_FLAG_")]
         	public static enum Flag {
 			IS_VALID =    0x0001,
 			CAN_ENCRYPT = 0x0002,
 			CAN_SIGN =    0x0004,
 			EXPIRED =     0x0100,
 			REVOKED =     0x0200,
 			DISABLED =    0x0400,
 			TRUSTED =     0x1000,
 			EXPORTABLE =  0x00100000
         	}

		public weak Seahorse.Context context;
		public GLib.List<weak Seahorse.Object> get_children ();
		public GLib.Quark tag { get; }
		public GLib.Quark id { get; }
		public Seahorse.Location location { get; set; }
		public Seahorse.Usage usage { get; }
		public uint flags { get; }
		public Seahorse.Source source { get; set; }
		public Seahorse.Object preferred { get; set; }
		public abstract string# label { get; }
		public abstract string# markup { get; }
		public abstract string# icon { get; }
		public Seahorse.Object? parent { get; set; }
		[CCode (cheader_filename = "seahorse-object.h")]
		public struct Predicate {
			public GLib.Quark tag;
			public GLib.Quark id;
			public Seahorse.Location location;
			public Seahorse.Usage usage;
			public uint flags;
			public uint nflags;
			public weak Seahorse.Source? source;
			public Seahorse.Object.PredicateFunc? custom;
			public bool match (Seahorse.Object obj);
		}
		[CCode (cheader_filename = "seahorse-object.h")]
		public delegate bool PredicateFunc (Seahorse.Object obj);
	}
	[CCode (cheader_filename = "seahorse-servers.h")]
	public class Servers : GLib.Object {
		public static GLib.SList<string> get_types ();
		public static string? get_description (string type);
		public static void register_type (string type, string description, Seahorse.ValidUriFunc validate);
		public static GLib.SList<string> get_uris ();
		public static GLib.SList<string> get_names ();
		public static bool is_valid_uri (string uri);
		public Servers ();
	}
	[CCode (cheader_filename = "seahorse-view.h")]
	public interface View : GLib.Object {
		public abstract GLib.List<weak Seahorse.Object> get_selected_objects ();
		public abstract void set_selected_objects (GLib.List<Seahorse.Object> objects);
		public abstract Seahorse.Object? selected { get; set; }
		public abstract Seahorse.Set? current_set { get; }
		public abstract Gtk.Window window { get; }
		public signal void selection_changed ();
	}
	[CCode (cheader_filename = "seahorse-servers.h")]
	public static delegate bool ValidUriFunc (string uri);
}
