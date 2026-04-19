# Installation — World Builder Templates

1. Close the Unreal Editor.
2. Copy the entire **`WorldBuilderTemplates`** folder (containing `WorldBuilderTemplates.uplugin` and `Source/`) into your project’s **`Plugins`** directory, for example:
   - `YourProject/Plugins/WorldBuilderTemplates/`
3. Right-click **`YourProject.uproject`** → **Generate Visual Studio project files** (or use your preferred method).
4. Open the solution and build the **Development Editor** configuration.
5. Launch the editor, open **Edit → Plugins**, search **World Builder Templates**, enable it, and restart if asked.

Optional: add more level assets under `Plugins/WorldBuilderTemplates/Content/`.  
Optional: **Edit → Project Settings → Plugins → World Builder Templates** to add extra **package path roots** (e.g. other engine template folders). Defaults already include `/Engine/Maps/Templates` alongside this plugin’s mount.
