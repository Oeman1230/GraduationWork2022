from pathlib import Path
import os
from functools import singledispatch


class WorkWithStringsErrors(Exception):
    pass


class FileWithNoNumber(WorkWithStringsErrors):
    pass


class FileWithoutScopes(WorkWithStringsErrors):
    pass


class FileWithoutExtension(WorkWithStringsErrors):
    pass


class WorkWithStrings:
    def __init__(self):
        pass

    left_scope = "_("
    right_scope = ")"
    WWS = "WWS."

    # @staticmethod
    # def cut_out_last_str_by_sep(name: str, sep: str):
    #     ret_val = name.rsplit(sep, 1)
    #     return ret_val[0]
    @staticmethod
    def pth_append(path_str: str, addit_path):
        return f"{path_str}/{addit_path}"

    @staticmethod
    def cut_out_extension(ext: str):
        ret_val = ext.rsplit(".", 1)
        # except IndexError:
        #     raise FileWithoutExtension
        # print(ret_val)
        return ret_val




    # @staticmethod
    # def separate_str_file_name_by(names_list, sep_sign_1, sep_sign_2):
    #     ret_list = list()
    #     for elem in names_list:
    #         elem_no_ext = WorkWithStrings.cut_out_extension(str(elem))
    #         pass
    FND_STR_M_MIDDLE = "Middle mode"
    FND_STR_M_FRST_PART = "First part mode"

    @staticmethod
    def find_string_between_seps(name: str, sep_sign_first: str = left_scope, sep_sign_second: str = right_scope,
                                 FND_STR_mode=None):
        try:
            elem_no_ext = WorkWithStrings.cut_out_extension(name)[0]
        except IndexError:
            raise FileWithoutExtension(f"No extension in {name}")
        # print(f"elem no ext: {elem_no_ext}")
        try:
            elem_cut_first_part = elem_no_ext.rsplit(sep_sign_first, 1)[1]
        except IndexError:
            raise FileWithoutScopes("No ", sep_sign_first, " in ", name)
        # print(f"ele cut last: {elem_cut_first_part}")
        try:
            middle_string = elem_cut_first_part.rsplit(sep_sign_second, 1)[0]
        except IndexError:
            raise FileWithoutScopes("No ", sep_sign_second, " in ", name)

        # print(f"middle elem: {middle_string}")

        if FND_STR_mode == WorkWithStrings.FND_STR_M_FRST_PART:
            return elem_no_ext.rsplit(sep_sign_first, 1)[0]
        return middle_string

    # @staticmethod
    # def get_string_without_seps

    @staticmethod
    def get_int_num_in_string(str_name, first_scope=left_scope,
                              second_scope=right_scope):
        try:
            str_int = WorkWithStrings.find_string_between_seps(str_name, first_scope, second_scope)
        except FileWithoutScopes:
            raise FileWithoutScopes(f"No scopes in ", str_name)
        # print(f"int num: {str_int}")
        if not str_int:
            raise FileWithNoNumber(f"Nothing in ", str_name)
        if not str_int.isdigit():
            raise WorkWithStringsErrors(f"in {str_name}_() not number")
        ret_val = int(str_int)
        return ret_val

    @staticmethod
    def pack_smth_in_seps_in_one_string(name_with_ext, input_text_btw_seps, left_sep=left_scope,
                                        right_sep=right_scope):
        try:
            str_inp_ext = WorkWithStrings.cut_out_extension(name_with_ext)[1]
            str_ext = "." + str_inp_ext
        except IndexError:
            str_ext = ""
        # new_text_in_scope = WorkWithStrings.find_string_between_seps(name_with_ext, left_sep, right_sep)
        rename_name = f"{WorkWithStrings.cut_out_extension(name_with_ext)[0]}{left_sep}"\
                      f"{input_text_btw_seps}{right_sep}{str_ext}"
        return rename_name

    @staticmethod
    def increase_value_in_scopes_and_pack(name_with_num_and_ext, left_sep=left_scope, right_sep=right_scope):
        new_num = int
        try:
            file_number = WorkWithStrings.get_int_num_in_string(name_with_num_and_ext, left_sep, right_sep)
            new_num = file_number + 1

            file_ext = WorkWithStrings.cut_out_extension(name_with_num_and_ext)[1]

            file_name_no_scopes = WorkWithStrings.find_string_between_seps(
                name_with_num_and_ext, FND_STR_mode=WorkWithStrings.FND_STR_M_FRST_PART)
            rename_name = WorkWithStrings.pack_smth_in_seps_in_one_string(f"{file_name_no_scopes}.{file_ext}",
                                                                          new_num)
            # print(f"Normal work increase: {rename_name}")
        except FileWithNoNumber:
            rename_name = WorkWithStrings.pack_smth_in_seps_in_one_string(name_with_num_and_ext, 1,
                                                                          left_sep, right_sep)
            # print(f"FileWithNoNum {rename_name}")
            return rename_name
        except IndexError:
            file_name_no_ext = WorkWithStrings.find_string_between_seps(
                name_with_num_and_ext, FND_STR_mode=WorkWithStrings.FND_STR_M_FRST_PART)
            rename_name = WorkWithStrings.pack_smth_in_seps_in_one_string(file_name_no_ext, new_num)
        except FileWithoutScopes:
            name_without_scopes = name_with_num_and_ext
            rename_name = WorkWithStrings.pack_smth_in_seps_in_one_string(name_without_scopes, 1,
                                                                          left_sep, right_sep)
            # print(f"FileWithoutScopes {rename_name}")
            return rename_name

        # rename_name = WorkWithStrings.pack_smth_in_seps_in_one_string(
        #     WorkWithStrings.find_string_between_seps(name_with_num_and_ext,
        #                                              FND_STR_mode=WorkWithStrings.FND_STR_M_FRST_PART),
        #     file_number + 1, left_sep, right_sep)

        return rename_name


