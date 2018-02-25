

project "rtrad"
kind "StaticLib"
language "C"
defines {
    "lint"
}
files {
    rad_common.."/addobjnotify.c", 
    rad_common.."/badarg.c",
    rad_common.."/biggerlib.c",
    rad_common.."/bmalloc.c",
    rad_common.."/bmpfile.c",
    rad_common.."/bsdf.c",
    rad_common.."/bsdf_m.c",        
    rad_common.."/bsdf_t.c",
    rad_common.."/byteswap.c",
    rad_common.."/caldefn.c",
    rad_common.."/calexpr.c",
    rad_common.."/calfunc.c",
    rad_common.."/calprnt.c",
    rad_common.."/ccolor.c",
    rad_common.."/ccyrgb.c",        
    rad_common.."/chanvalue.c",
    rad_common.."/clip.c",
    rad_common.."/color.c",
    rad_common.."/colrops.c",
    rad_common.."/cone.c",
    rad_common.."/cvtcmd.c",
    rad_common.."/dircode.c",
    rad_common.."/disk2square.c",
    rad_common.."/ealloc.c",
    rad_common.."/eputs.c",
    rad_common.."/erf.c",
    rad_common.."/error.c",
    rad_common.."/expandarg.c",
    rad_common.."/ezxml.c",
    rad_common.."/face.c",
    rad_common.."/falsecolor.c",
    rad_common.."/fdate.c",
    rad_common.."/fgetline.c",
    rad_common.."/fgetval.c",
    rad_common.."/fgetword.c",
    rad_common.."/fixargv0.c",
    rad_common.."/font.c",
    rad_common.."/fputword.c",    
    rad_common.."/fropen.c",
    rad_common.."/fvect.c",
    rad_common.."/gethomedir.c",
    rad_common.."/getlibpath.c",
    rad_common.."/getpath.c",
    rad_common.."/header.c",
    rad_common.."/hilbert.c",        
    rad_common.."/image.c",
    rad_common.."/instance.c",
    rad_common.."/invmat4.c",
    rad_common.."/lamps.c",
    rad_common.."/linregr.c",
    rad_common.."/loadbsdf.c",
    rad_common.."/loadvars.c",
    rad_common.."/lookup.c",        
    rad_common.."/mat4.c",
    rad_common.."/mesh.c",
    rad_common.."/modobject.c",
    rad_common.."/multisamp.c",
    rad_common.."/myhostname.c",
    rad_common.."/objset.c",
    rad_common.."/octree.c",
    rad_common.."/otypes.c",        
    rad_common.."/paths.c",
    rad_common.."/plocate.c",
    rad_common.."/portio.c",
    rad_common.."/process.c",
    rad_common.."/quit.c",
    rad_common.."/readfargs.c",
    rad_common.."/readmesh.c",
    rad_common.."/readobj.c",        
    rad_common.."/readoct.c",
    rad_common.."/resolu.c",
    rad_common.."/rexpr.c",
    rad_common.."/savqstr.c",
    rad_common.."/savestr.c",
    rad_common.."/sceneio.c",
    rad_common.."/spec_rgb.c",
    rad_common.."/tcos.c",        
    rad_common.."/tmap16bit.c",
    rad_common.."/tmapcolrs.c",
    rad_common.."/tmapluv.c",
    rad_common.."/timegm.c",
    rad_common.."/tmaptiff.c",
    rad_common.."/tmesh.c",
    rad_common.."/tonemap.c",        
    rad_common.."/triangulate.c",
    rad_common.."/urand.c",
    rad_common.."/urind.c",
    rad_common.."/words.c",
    rad_common.."/wordfile.c",
    rad_common.."/wputs.c",
    rad_common.."/xf.c",
    rad_common.."/zeroes.c"
}
targetdir (libs_dir.."/%{cfg.platform}".."/%{cfg.buildcfg}")   
includedirs{
    emp_core_dir.."/3rdparty/Radiance/src/**",
    emp_core_dir.."/3rdparty"
}