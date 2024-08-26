# ChatGPT
import os
import subprocess
import sys



def extract_masks(directory):
    # Ensure the directory exists
    if not os.path.exists(directory):
        print(f"Directory {directory} does not exist.")
        return

    # Loop through all .djvu files in the specified directory
    for filename in os.listdir(directory):
        if filename.endswith(".djvu"):
            djvu_file = os.path.join(directory, filename)
            base_name = os.path.splitext(djvu_file)[0]
            pbm_file = f"{base_name}_mask.pbm"
            png_file = f"{base_name}_mask.png"

            # Step 1: Extract the mask
            subprocess.run(["ddjvu", "-format=pbm", "-mode=mask", djvu_file, pbm_file])

            # Step 2: Convert PBM to PNG using ImageMagick
            subprocess.run(["convert", pbm_file, png_file])

            # Step 3: Keep the PBM file for further investigation

            print(f"Processed {djvu_file}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python djvu2maskBF.py <directory_path>")
    else:
        directory = sys.argv[1]
        extract_masks(directory)


#            print(f"Processed {djvu_file}")

# Example usage
# directory = "/home/jsbien/git/early_fonts_inventory/font_tables/oDjvu"
# extract_masks(directory)
