# Scripts
Here are some useful scripts for development.
The `.bin` files aren't saved.

## Verify
Verify compiles all cpp files in the directory for the Photon, creates a `.bin` file, and then deletes it. Similar to the web IDE verify button.

## Upload
Sets the Particle Photon into DFU mode via USB, compiles cpp files in the directory for the Photon, creates a `.bin` file, uploads the `.bin` file to the Photon, and finally deletes the `.bin` file.

## Troubleshooting
If the scripts are not executing, change the permission.
```bash
$ chmod +x *.sh
```
