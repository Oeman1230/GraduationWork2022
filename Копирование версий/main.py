import shutil

from FileWorking import WorkWithFiles
from FileWorking import WorkWithStrings
from pathlib import Path
import os
from UserInterface import UserInterface


def sep_line_print():
    print("*" * 100)


# Я тестирую работу с файлами, с их перемещениями.
# Моя задача, в целом, сделать программу для копирования файлов в
# указанный мной каталог, в котором создаст новую папку с номером,
# который больше предыдущего на 1. Почти система контроля версий,
# только моя
backup_string_path = r"SouceCppFolder\\BackupCpp"
source_cpp_folder = "SouceCppFolder"
ext_str = "*.txt"
cur_d = WorkWithFiles.PWD

# WorkWithFiles.create_dir_with_path(source_cpp_folder)
# WorkWithFiles.create_dir_with_path(backup_string_path)
# WorkWithFiles.print_list(WorkWithFiles.find_files_by_extension(WorkWithFiles.PWD, ext_str))
# WorkWithFiles.move_files_from_to_pack(backup_string_path, ext_str, cur_d)

# files_list_1 = WorkWithFiles.str_files_with_extension_to_list_with_files(cur_d, ext_str)
# files_list_2 = WorkWithFiles.str_files_with_extension_to_list_with_files(backup_string_path, ext_str)
# pip list
# pip show

# -2793483536799882080
# -800 100 -2700

txt_1 = "1.txt"
txt_2 = "2.txt"
txt_3 = "1.18.1.txt"
txt_4 = "1_(num)_(10).txt"
dat_1 = "datName.dat"
no_txt = ""
new_txt = txt_1


# WWS = WorkWithStrings
WWF = WorkWithFiles
# destination_dir_path = WWS.pth_append(
#     WorkWithFiles.PWD, WWS.pth_append(source_cpp_folder, "test_dir"))
# print(WWF.get_path())
# print(len(WWF.find_files_by_extension(WWF.get_path(), ".py")))
# for elem in Path(r"C:\Users\Yury\PycharmProjects\pythonProject").glob("*.py"):
#     print(elem.name)
# print()
WWF.make_version_folder_with_files(r"E:\сортировка\IpsGame", r"E:\сортировка\IpsGame\Versions", 1, 2)

# print(os.listdir(source_cpp_folder))

# UIF = UserInterface()
# UIF.main_menu_run()

# WorkWithFiles.make_version_folder_with_files(r"C:\Users\Yury\PycharmProjects\pythonProject", "Versions", 1, 1,
#                                              point_ext_list=["*.py"])

# WWF.copy_files_with_ext_in_folder_to_folder("Old comments", "txt", "Old comments")
#
#
# def find_dirs_get_list(source_path_str_absolute: str, path_mode=False):
#     ret_val = list()
#     src_path = Path(source_path_str_absolute)
#     ls = os.listdir(src_path)
#     for elem in ls:
#         cur_elem = Path(f"{source_path_str_absolute}/{elem}")
#         if os.path.isdir(cur_elem):
#             ret_val.append(cur_elem)
#         else:
#             continue
#     if path_mode:
#         return ret_val
#     ret_val_str = list()
#     for elem in ret_val:
#         ret_val_str.append(elem.name)
#     return ret_val_str
#
#
# # WWF.print_list(find_dirs_get_list(f"{WWF.PWD}/{source_cpp_folder}"))
#
#
# def copy_folder(source_dir_path_absolute_str: str, new_dir_name: str, destination_dir_absolute_str: str):
#     src_pth_abs = Path(source_dir_path_absolute_str)
#     dest_dir_abs = Path(destination_dir_absolute_str)
#     print(src_pth_abs)
#     print(dest_dir_abs)
#     new_folder = WorkWithStrings.pth_append(destination_dir_absolute_str, new_dir_name)
#     if not os.path.exists(new_folder):
#         shutil.copytree(src_pth_abs, new_folder)
#         print(new_folder)
#         return True
#     else:
#         return False
#
#
# def copy_folder_with_name_num_increase(source_dir_path_absolute_str: str, destination_dir_absolute_str: str):
#     src_pth_abs = Path(source_dir_path_absolute_str)
#     dest_dir_abs = Path(destination_dir_absolute_str)
#     if not dest_dir_abs.exists() or not src_pth_abs.exists():
#         return False
#     dest_dirs_list = find_dirs_get_list(destination_dir_absolute_str)
#     new_dir_name = src_pth_abs.name
#     # print(new_dir_name)
#     copying_success = False
#     while not copying_success:
#         if new_dir_name not in dest_dirs_list:
#             print(new_dir_name)
#             # WWF.print_list(dest_dirs_list)
#             success = copy_folder(source_dir_path_absolute_str, new_dir_name, destination_dir_absolute_str)
#             # print(success)
#             copying_success = True
#             print("end")
#         else:
#             new_dir_name = WorkWithStrings.increase_value_in_scopes_and_pack(new_dir_name)
#             # print("cf_else", new_dir_name)
#             continue
#     return True


# print(destination_dir_path)
# ret = WWF.copy_folder_with_name_num_increase(destination_dir_path, WWF.PWD.absolute())
# print(ret)


# shutil.copytree("SouceCppFolder/test_dir", "./test_dir1")
# WorkWithFiles.move_files_from_to_pack(cur_d, ext_str, backup_string_path)
# WorkWithFiles.move_files_from_to_pack(backup_string_path, ext_str, cur_d)


