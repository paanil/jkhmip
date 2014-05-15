bl_info = {
    'name': 'MyScene exporter (.scene)',
    'author': 'Ilari Paananen',
    'version': (1, 0, 0),
    'blender': (2, 5, 7),
    'api': 34786,
    'location': "File > Export",
    'description': 'Export MyScene',
    'category': 'Import-Export'}

import bpy
from bpy_extras.io_utils import ExportHelper
from struct import pack

class ExportMyScene(bpy.types.Operator, ExportHelper):
    bl_idname = "my_scene.export"
    bl_label = "Export MyScene (.scene)"

    filename_ext = ".scene"
    filepath = bpy.props.StringProperty(subtype="FILE_PATH")

    node_types = {
        'DUMMY': 0,
        'MESH': 1,
        'LAMP': 2}

    next_id = 1

    def get_ob_type(self, ob):
        try:
            ob_type = self.node_types[ob.type]
            return ob_type
        except:
            return self.node_types['DUMMY']

    def get_next_id(self):
        next_id = self.next_id
        self.next_id = self.next_id + 1
        return next_id

    def write_mat(self, f, m):
        f.write(pack("=4f", m[0][0], m[0][2], m[0][1], m[0][3]))
        f.write(pack("=4f", m[2][0], m[2][2], m[2][1], m[2][3]))
        f.write(pack("=4f", m[1][0], m[1][2], m[1][1], m[1][3]))

    def write_ob(self, f, ob, parent_id):
        ob_type = self.get_ob_type(ob)
        ob_id = self.get_next_id()
        f.write(pack("=3i", ob_type, ob_id, parent_id))
        self.write_mat(f, ob.matrix_local)
        if ob_type == self.node_types['MESH']:
            name = ob.data.name.encode()
            f.write(pack("31sc", name, b'\x00'))
        elif ob_type == self.node_types['LAMP']:
            radius = -1
            if ob.data.type == 'POINT':
                radius = ob.data.distance
            color = ob.data.color
            energy = ob.data.energy
            f.write(pack("=5f", radius, color.r, color.g, color.b, energy))
        for child in ob.children:
            self.write_ob(f, child, ob_id)

    def execute(self, context):
        f = open(self.filepath, "wb")
        sce = context.scene
        for ob in sce.objects:
            if ob.parent == None:
                self.write_ob(f, ob, 0)
        f.close()
        return {"FINISHED"}

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {"RUNNING_MODAL"}

def menu_func(self, context):
    self.layout.operator(ExportMyScene.bl_idname, text="MyScene (.scene)...")

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
