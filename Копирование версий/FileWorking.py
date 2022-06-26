
from pathlib import Path
import os
from functools import singledispatch
from WorkWithStrings import WorkWithStrings, FileWithNoNumber, WorkWithStringsErrors, FileWithoutScopes
import shutil
# import shutil
# os.remove(f"{cur_d}/1_copy.txt")
# shutil.copy(f"{backup_string_path}/1.txt", f"{cur_d}/1_copy.txt")


class WorkWithFilesErrors(Exception):
    pass


class WorkWithFiles:
    yes_t = " yes "
    no_t = " no "
    WWF = "WWF."

    def __init__(self):
        pass

    @staticmethod
    # функция вывода на экран списка
    def print_list(printing_list):
        for elem in printing_list:
            print(elem)

    @staticmethod
    # создание папки с данным именем
    def create_dir_with_path(dir_path: Path):
        if not os.path.exists(dir_path):
            os.mkdir(dir_path)
            print(f"{dir_path} created")
            return True
        else:
            print(f"{dir_path} exists")
            return False

    @staticmethod
    def copy_dir_to_new_dir(source_dir_path_absolute, destination_dir_path_absolute):
        pass

    @staticmethod
    # Функция перевода генератора в лист
    def gen_to_list(gen_name):
        new_list = list()
        for gen_elem in gen_name:
            new_list.append(gen_elem)
        return new_list

    @singledispatch
    def find_files_by_extension(source, extension_str):
        raise WorkWithFilesErrors("Not supported type")

    @find_files_by_extension.register
    def _(source: str, extension_str):
        ret_val = list()
        # print(f"source_str in find_by_ext: {source}")
        source_file = Path(source)
        if not source_file.exists():
            raise WorkWithFilesErrors(f"No files founded")
        # print(f"find_by_ext:{source_folder.name}")
        try:
            for elem in source_file.glob(extension_str):
                ret_val.append(elem)
        except IndexError:
            raise IndexError("Incorrect inserted arguments")
        return ret_val

    @staticmethod
    def get_path():
        return Path.cwd()

    PWD = get_path()

    @find_files_by_extension.register
    def _(source: Path, extension_str):
        ret_val = list()
        print(f"source_path in find_by_ext: {source}")
        source_file = source
        if not source_file.exists():
            raise WorkWithFilesErrors(f"No files founded")
        # print(f"find_by_ext:{source_folder.name}")
        try:
            print("try path")
            print(source_file.glob(extension_str))
            for elem in source_file.glob(extension_str):
                print(elem.name)
                ret_val.append(elem)
        except IndexError:
            raise IndexError("Incorrect inserted arguments")
        return ret_val

    # @staticmethod
    # # Функция поиска файлов
    # def find_files_by_extension(source_str, extension_str):
    #     ret_val = list()
    #     print(f"source_str in find_by_ext: {source_str}")
    #     source_folder = Path(source_str)
    #     if not source_folder.exists():
    #         raise WorkWithFilesErrors(f"No files founded")
    #
    #     print(f"find_by_ext:{source_folder.name}")
    #     try:
    #         for elem in source_folder.glob(extension_str):
    #             ret_val.append(elem)
    #     except IndexError as glob_index_err:
    #         raise IndexError("Incorrect inserted arguments")
    #     return ret_val

    @staticmethod
    def str_files_with_extension_to_list_with_files(source_str, extension_str):
        ret_val = WorkWithFiles.gen_to_list(WorkWithFiles.find_files_by_extension(source_str, extension_str))
        return ret_val


    @staticmethod
    def join_destination_folder():
        pass

    @staticmethod
    def path_list_to_names_list(paths_list):
        ret_list = list()
        for elem in paths_list:
            ret_list.append(elem.name)
        return ret_list

    @staticmethod
    def _MV_FLS_FRM_PCK_TO_PCK_dest_path_ext_to_dest_files_names(extension_str, destination_path_str):
        destination_files_list = WorkWithFiles.str_files_with_extension_to_list_with_files(destination_path_str,
                                                                                           extension_str)
        destination_files_names_list = WorkWithFiles.path_list_to_names_list(destination_files_list)
        return destination_files_names_list

    @staticmethod
    def move_files_from_to_pack(source_str, extension_str, destination_path_str):
        source_files_list = WorkWithFiles.str_files_with_extension_to_list_with_files(source_str, extension_str)

        destination_files_names_list = WorkWithFiles._MV_FLS_FRM_PCK_TO_PCK_dest_path_ext_to_dest_files_names(
            extension_str, destination_path_str)
        # destination_files_list[0]
        destination_path = Path(destination_path_str)
        # print(WorkWithFiles.WWF + "mfftp - pre for in srcfiles")
        for src_elem in source_files_list:
            # print(WorkWithFiles.WWF + "mfftp - for in srcfiles")
            if src_elem.name in destination_files_names_list:
                print(WorkWithFiles.WWF + "true))")

                file_add_name = Path(src_elem).name
                try:
                    WorkWithStrings.get_int_num_in_string(file_add_name)
                except FileWithoutScopes:
                    file_add_name = WorkWithStrings.increase_value_in_scopes_and_pack(file_add_name)
                destination_files_names_list = \
                    WorkWithFiles._MV_FLS_FRM_PCK_TO_PCK_dest_path_ext_to_dest_files_names(
                        extension_str, destination_path_str)
                temp_file_name = file_add_name
                while temp_file_name in destination_files_names_list:
                    temp_file_name = WorkWithStrings.increase_value_in_scopes_and_pack(temp_file_name)

                new_name = temp_file_name
                dest = destination_path.joinpath(new_name)
                Path(src_elem).rename(dest)
            else:
                print(WorkWithFiles.WWF + "False")
                file_name = Path(src_elem).name
                dest = destination_path.joinpath(file_name)
                Path(src_elem).rename(dest)

    @staticmethod
    def copy_files_with_ext_in_folder_to_folder(source_dir_str, ext_str, destination_dir_path_str):
        # print(WorkWithFiles.WWF + "cfweifwf")
        # print(WorkWithFiles.WWF + "start")
        if not Path(destination_dir_path_str).exists():
            shutil.copytree(source_dir_str, destination_dir_path_str)  # копирует папку с её содержимым
        else:
            # print(WorkWithFiles.WWF + "start")
            WorkWithFiles.move_files_from_to_pack(source_dir_str, ext_str, destination_dir_path_str)
            # print(WorkWithFiles.WWF + "end")

    @staticmethod
    def find_dirs_get_list(source_path_str_absolute: str, path_mode=False):
        ret_val = list()
        src_path = Path(source_path_str_absolute)
        ls = os.listdir(src_path)
        for elem in ls:
            cur_elem = Path(f"{source_path_str_absolute}/{elem}")
            if os.path.isdir(cur_elem):
                ret_val.append(cur_elem)
            else:
                continue
        if path_mode:
            return ret_val
        ret_val_str = list()
        for elem in ret_val:
            ret_val_str.append(elem.name)
        return ret_val_str

    @staticmethod
    def copy_folder(source_dir_path_absolute_str: str, new_dir_name: str, destination_dir_absolute_str: str):
        src_pth_abs = Path(source_dir_path_absolute_str)
        dest_dir_abs = Path(destination_dir_absolute_str)
        # print(src_pth_abs)
        # print(dest_dir_abs)
        new_folder = WorkWithStrings.pth_append(destination_dir_absolute_str, new_dir_name)
        if not os.path.exists(new_folder):
            shutil.copytree(src_pth_abs, new_folder)
            # print(new_folder)
            return True
        else:
            return False

    @staticmethod
    def copy_folder_with_name_num_increase(source_dir_path_absolute_str: str, destination_dir_absolute_str: str):
        src_pth_abs = Path(source_dir_path_absolute_str)
        dest_dir_abs = Path(destination_dir_absolute_str)
        if not dest_dir_abs.exists() or not src_pth_abs.exists():
            return False
        dest_dirs_list = WorkWithFiles.find_dirs_get_list(destination_dir_absolute_str)
        new_dir_name = src_pth_abs.name
        # print(new_dir_name)
        copying_success = False
        while not copying_success:
            if new_dir_name not in dest_dirs_list:
                # print(new_dir_name)
                # WWF.print_list(dest_dirs_list)
                success = WorkWithFiles.copy_folder(source_dir_path_absolute_str, new_dir_name, destination_dir_absolute_str)
                # print(success)
                copying_success = True
                print("end")
            else:
                new_dir_name = WorkWithStrings.increase_value_in_scopes_and_pack(new_dir_name)
                # print("cf_else", new_dir_name)
                continue
        return True

    @staticmethod
    def make_version_folder_with_files(source_dir_absolute_path_str: str, versions_dir_absolute_path_str: str,
                                       version_realise_num: int, version_update_num: int,
                                       point_ext_list: list = ["*.cpp", "*.h"]):
        src_dir_abs_pth = Path(source_dir_absolute_path_str).absolute()
        ver_dir_abs_pth = Path(versions_dir_absolute_path_str).absolute()
        WorkWithFiles.create_dir_with_path(ver_dir_abs_pth.joinpath(str(versions_dir_absolute_path_str)))
        realise_num_dir = ver_dir_abs_pth.joinpath(str(version_realise_num))
        WorkWithFiles.create_dir_with_path(realise_num_dir)
        # print("realise_num_dir: " + str(realise_num_dir))
        version_update = realise_num_dir.joinpath(str(version_update_num))
        # print("version_update: " + str(version_update))
        WorkWithFiles.create_dir_with_path(version_update)

        src_folder_name = src_dir_abs_pth.name
        temp_src_dir = src_dir_abs_pth.joinpath(src_folder_name)
        WorkWithFiles.create_dir_with_path(temp_src_dir)
        # WorkWithFiles.print_list(WorkWithFiles.str_files_with_extension_to_list_with_files(
        #     str(src_dir_abs_pth.absolute()), "*.cpp"))
        for ext_elem in point_ext_list:
            moving_files = WorkWithFiles.find_files_by_extension(src_dir_abs_pth.absolute(), ext_elem)
            WorkWithFiles.print_list(moving_files)
            for file in moving_files:
                p_file = Path(file)
                shutil.copy(p_file, temp_src_dir.joinpath(p_file.name))

        WorkWithFiles.copy_folder_with_name_num_increase(temp_src_dir, version_update)
        shutil.rmtree(temp_src_dir, ignore_errors=True)
        # # vers_dir_pth = Path(versions_dir_absolute_path_str).absolute()
        # destination_pth_ver_num_str = WorkWithStrings.pth_append(versions_dir_absolute_path_str,
        #                                                          str(version_realise_num))
        # WorkWithFiles.create_dir_with_path(destination_pth_ver_num_str)
        # destination_pth_ver_update_num_str = WorkWithStrings.pth_append(destination_pth_ver_num_str,
        #                                                                 version_update_num)
        # WorkWithFiles.create_dir_with_path(destination_pth_ver_update_num_str)
        # new_version = src_dir_pth.name
        #
        # # versions_list =
        #
        # new_version = WorkWithStrings.increase_value_in_scopes_and_pack(new_version)

