bl_info = {
    'name': 'TheScene exporter (.scene)',
    'author': 'Ilari Paananen',
    'version': (1, 0, 0),
    'blender': (2, 5, 7),
    'api': 34786,
    'location': "File > Export",
    'description': 'Export TheScene',
    'category': 'Import-Export'}

import bpy
from bpy_extras.io_utils import ExportHelper
from struct import pack

class ExportTheScene(bpy.types.Operator, ExportHelper):
    bl_idname = "the_scene.export"
    bl_label = "Export TheScene (.scene)"

    filename_ext = ".scene"
    filepath = bpy.props.StringProperty(subtype="FILE_PATH")

    node_types = {
        'DUMMY': 0,
        'MESH': 1,
        'LAMP': 2}

    lamp_types = {
        'SUN': 0,
        'SPOT': 1,
        'POINT': 2}

    prop_names = {
        0: 'rotate_x',
        1: 'rotate_y',
        2: 'rotate_z'}

    num_prop_types = 3

    next_id = 1

    class Prop:
        def __init__(self, ob_id, prop, val):
            self.ob = ob_id
            self.prop = prop
            self.val = val

    props = []

    def get_ob_type(self, ob):
        if ob.name == "sky":
            return 3
        try:
            ob_type = self.node_types[ob.type]
            return ob_type
        except:
            return self.node_types['DUMMY']

    def get_lamp_type(self, lamp):
        try:
            lamp_type = self.lamp_types[lamp.type]
            return lamp_type
        except:
            return self.lamp_types['SUN']

    def get_next_id(self):
        next_id = self.next_id
        self.next_id = self.next_id + 1
        return next_id

    def write_mat(self, f, m):
        f.write(pack("=4f", m[0][0], m[0][2], m[0][1], m[0][3]))
        f.write(pack("=4f", m[2][0], m[2][2], m[2][1], m[2][3]))
        f.write(pack("=4f", m[1][0], m[1][2], m[1][1], m[1][3]))

    def write_lamp(self, f, lamp):
        lamp_type = self.get_lamp_type(lamp);
        radius = 0.0;
        cutoff = 0.0;
        if lamp_type == self.lamp_types['POINT']:
            radius = lamp.distance
        elif lamp_type == self.lamp_types['SPOT']:
            radius = lamp.distance
            cutoff = lamp.spot_size / 2.0;
        color = lamp.color
        energy = lamp.energy
        f.write(pack("=i", lamp_type))
        f.write(pack("=f", radius))
        f.write(pack("=f", cutoff))
        f.write(pack("=3f", color.r, color.g, color.b))
        f.write(pack("=f", energy))

    def try_append_prop(self, ob, ob_id, prop_type):
        try:
            prop_name = self.prop_names[prop_type]
            prop_val = ob[prop_name]
            prop = ExportTheScene.Prop(ob_id, prop_type, prop_val)
            self.props.append(prop)
        except:
            pass

    def append_custom_props(self, ob, ob_id):
        for i in range(0, self.num_prop_types):
            self.try_append_prop(ob, ob_id, i)

    def write_ob(self, f, ob, parent_id):
        ob_type = self.get_ob_type(ob)
        ob_id = self.get_next_id()
        f.write(pack("=3i", ob_type, ob_id, parent_id))
        self.write_mat(f, ob.matrix_local)
        if ob_type == self.node_types['MESH'] or ob_type == 3:
            cast_shadows = ob.active_material.use_cast_buffer_shadows
            if cast_shadows:
                f.write(pack("=i", 1))
            else:
                f.write(pack("=i", 0))
            name = ob.data.name.encode()
            f.write(pack("31sc", name, b'\x00'))
        elif ob_type == self.node_types['LAMP']:
            self.write_lamp(f, ob.data)
        self.append_custom_props(ob, ob_id)
        for child in ob.children:
            self.write_ob(f, child, ob_id)

    def write_custom_props(self, f):
        f.write(pack("=i", len(self.props)))
        for p in self.props:
            f.write(pack("=2i", p.ob, p.prop))
            f.write(pack("=f", p.val))

    def execute(self, context):
        self.props = []
        f = open(self.filepath, "wb")
        sce = context.scene
        f.write(pack("=i", len(sce.objects)))
        for ob in sce.objects:
            if ob.parent == None:
                self.write_ob(f, ob, 0)
        self.write_custom_props(f)
        f.close()
        return {"FINISHED"}

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {"RUNNING_MODAL"}

def menu_func(self, context):
    self.layout.operator(ExportMyScene.bl_idname, text="TheScene (.scene)...")

def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_func)

def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_func)

if __name__ == "__main__":
    try:
        unregister()
    except:
        pass
    register()
