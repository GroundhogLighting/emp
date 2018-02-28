auto_solve = false -- Do not solve tasks, as there will be none.

function tdc1(s)
    print("=> "..s)
end

function tdc2(s)
    print("   ... "..s)
end

-- Location
tdc1("Location:")
location = get_location_data();
for k,v in pairs(location) do
    tdc2(k.." : "..v)
end

-- Layers
layers = get_layers_list()
nlayers = #layers
tdc1("There are "..nlayers.." layers in the model")

for i=1,nlayers do
    nobjects = count_layer_objects(layers[i])
    ninstances = count_layer_instances(layers[i])
    tdc2(layers[i].." has "..nobjects.." objects and "..ninstances.." ComponentInstances");
end

-- Materials
materials = get_materials_list()
nmaterials = #materials

for i=1,nmaterials do
    class = get_material_class(materials[i])    
    tdc2(materials[i].." is a "..class);
end

-- Get workplanes
wps = get_workplanes_list()
nwps = #wps
tdc1("There are "..nwps.." workplanes in the model")

for i=1,nwps do
    tdc2(wps[i].." has "..count_workplane_polygons(wps[i]).." Polygons");
end

-- Component Definitions
definitions = get_component_definitions_list()
ndefs = #definitions
tdc1("There are "..ndefs.." ComponentDefinitions in the model")

for i=1,ndefs do
    nobjects = count_component_definition_objects(definitions[i])
    ninstances = count_component_definition_instances(definitions[i])
    tdc2(definitions[i].." has "..nobjects.." objects and "..ninstances.." ComponentInstances");
end

