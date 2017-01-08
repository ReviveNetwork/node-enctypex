{
    "targets": [
        {
            "target_name": "enctypex",
            "sources": [ "enctypex_decoder.c", "enctype_shared.c", "enctype2_decoder.c", "NativeExtension.cc", "functions.cc" ],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
        }
    ],
}
