#ifndef MQI_IO_HPP
#define MQI_IO_HPP

#include <sys/mman.h>  //for io
#include <zlib.h>

#include <algorithm>
#include <complex>
#include <cstdint>
#include <iomanip>  // std::setprecision
#include <iostream>
#include <moqui/base/mqi_common.hpp>
#include <moqui/base/mqi_hash_table.hpp>
#include <moqui/base/mqi_roi.hpp>
#include <moqui/base/mqi_scorer.hpp>
#include <moqui/base/mqi_sparse_io.hpp>
#include <numeric>  //accumulate
#include <valarray>

// DCMTK includes for DICOM support
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/ofstd/ofcond.h>
#include <dcmtk/ofstd/ofstd.h>
#include <dcmtk/ofstd/ofstring.h>

namespace mqi {
namespace io {
///<  save scorer data to a file in binary format
///<  scr: scorer pointer
///<  scale: data will be multiplied by
///<  dir  : directory path. file name will be dir + scr->name + ".bin"
///<  reshape: roi is used in scorer, original size will be defined.
template <typename R>
void save_to_bin(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                 const std::string& filename);

template <typename R>
void save_to_bin(const R* src, const R scale, const std::string& filepath,
                 const std::string& filename, const uint32_t length);

template <typename R>
void save_to_npz(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                 const std::string& filename, mqi::vec3<mqi::ijk_t> dim, uint32_t num_spots);

template <typename R>
void save_to_npz2(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                  const std::string& filename, mqi::vec3<mqi::ijk_t> dim, uint32_t num_spots);

template <typename R>
void save_to_npz(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                 const std::string& filename, mqi::vec3<mqi::ijk_t> dim, uint32_t num_spots,
                 R* time_scale, R threshold);

template <typename R>
void save_to_bin(const mqi::key_value* src, const R scale, uint32_t max_capacity,
                 const std::string& filepath, const std::string& filename);

template <typename R>
void save_to_mhd(const mqi::node_t<R>* children, const double* src, const R scale,
                 const std::string& filepath, const std::string& filename, const uint32_t length);

template <typename R>
void save_to_mha(const mqi::node_t<R>* children, const double* src, const R scale,
                 const std::string& filepath, const std::string& filename, const uint32_t length);

template <typename R>
void save_to_dcm(const mqi::node_t<R>* children, const double* src, const R scale,
                 const std::string& filepath, const std::string& filename, const uint32_t length,
                 bool twoCentimeterMode = false);
}  // namespace io
}  // namespace mqi

///< Function to write key values into file
///< src: array and this array is copied
///<
template <typename R>
void mqi::io::save_to_bin(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                          const std::string& filename) {
    /// create a copy using valarray and apply scale

    unsigned int nnz = 0;
    std::vector<mqi::key_t> key1;
    std::vector<mqi::key_t> key2;
    std::vector<double> value;
    key1.clear();
    key2.clear();
    value.clear();
    for (int ind = 0; ind < src->max_capacity_; ind++) {
        if (src->data_[ind].key1 != mqi::empty_pair && src->data_[ind].key2 != mqi::empty_pair &&
            src->data_[ind].value > 0) {
            key1.push_back(src->data_[ind].key1);
            key2.push_back(src->data_[ind].key2);
            value.push_back(src->data_[ind].value * scale);
        }
    }

    printf("length %lu %lu %lu\n", key1.size(), key2.size(), value.size());

    /// open out stream
    std::ofstream fid_key1(filepath + "/" + filename + "_key1.raw",
                           std::ios::out | std::ios::binary);
    if (!fid_key1)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_key1.raw" << std::endl;

    /// write to a file
    fid_key1.write(reinterpret_cast<const char*>(&key1.data()[0]),
                   key1.size() * sizeof(mqi::key_t));
    fid_key1.close();

    std::ofstream fid_key2(filepath + "/" + filename + "_key2.raw",
                           std::ios::out | std::ios::binary);
    if (!fid_key2)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_key2.raw" << std::endl;

    /// write to a file
    fid_key2.write(reinterpret_cast<const char*>(&key2.data()[0]),
                   key2.size() * sizeof(mqi::key_t));
    fid_key2.close();

    std::ofstream fid_bin(filepath + "/" + filename + "_value.raw",
                          std::ios::out | std::ios::binary);
    if (!fid_bin)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_value.raw" << std::endl;

    /// write to a file
    fid_bin.write(reinterpret_cast<const char*>(&value.data()[0]), value.size() * sizeof(double));
    fid_bin.close();
}

///< Function to write array into file
///< src: array and this array is copied
///<
template <typename R>
void mqi::io::save_to_bin(const R* src, const R scale, const std::string& filepath,
                          const std::string& filename, const uint32_t length) {
    /// create a copy using valarray and apply scale
    std::valarray<R> dest(src, length);
    munmap(&dest, length * sizeof(R));
    dest *= scale;
    /// open out stream
    std::ofstream fid_bin(filepath + "/" + filename + ".raw", std::ios::out | std::ios::binary);
    if (!fid_bin)
        std::cout << "Cannot write :" << filepath + "/" + filename + ".raw" << std::endl;

    /// write to a file
    fid_bin.write(reinterpret_cast<const char*>(&dest[0]), length * sizeof(R));
    fid_bin.close();
}

///< Function to write key values into file
///< src: array and this array is copied
///<
template <typename R>
void mqi::io::save_to_bin(const mqi::key_value* src, const R scale, uint32_t max_capacity,
                          const std::string& filepath, const std::string& filename) {
    /// create a copy using valarray and apply scale

    unsigned int nnz = 0;
    std::vector<mqi::key_t> key1;
    std::vector<mqi::key_t> key2;
    std::vector<R> value;
    key1.clear();
    key2.clear();
    value.clear();
    for (int ind = 0; ind < max_capacity; ind++) {
        if (src[ind].key1 != mqi::empty_pair && src[ind].key2 != mqi::empty_pair &&
            src[ind].value > 0) {
            key1.push_back(src[ind].key1);
            key2.push_back(src[ind].key2);
            value.push_back(src[ind].value * scale);
        }
    }

    printf("length %lu %lu %lu\n", key1.size(), key2.size(), value.size());
    /// open out stream
    std::ofstream fid_key1(filepath + "/" + filename + "_key1.raw",
                           std::ios::out | std::ios::binary);
    if (!fid_key1)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_key1.raw" << std::endl;

    /// write to a file
    fid_key1.write(reinterpret_cast<const char*>(&key1.data()[0]),
                   key1.size() * sizeof(mqi::key_t));
    fid_key1.close();

    std::ofstream fid_key2(filepath + "/" + filename + "_key2.raw",
                           std::ios::out | std::ios::binary);
    if (!fid_key2)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_key2.raw" << std::endl;

    /// write to a file
    fid_key2.write(reinterpret_cast<const char*>(&key2.data()[0]),
                   key2.size() * sizeof(mqi::key_t));
    fid_key2.close();

    std::ofstream fid_bin(filepath + "/" + filename + "_value.raw",
                          std::ios::out | std::ios::binary);
    if (!fid_bin)
        std::cout << "Cannot write :" << filepath + "/" + filename + "_value.raw" << std::endl;

    /// write to a file
    fid_bin.write(reinterpret_cast<const char*>(&value.data()[0]), value.size() * sizeof(R));
    fid_bin.close();
}

///< Function to write key values into file
///< src: array and this array is copied
///<

template <typename R>
void mqi::io::save_to_npz(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                          const std::string& filename, mqi::vec3<mqi::ijk_t> dim,
                          uint32_t num_spots) {
    uint32_t vol_size;
    vol_size = dim.x * dim.y * dim.z;

    /// create a copy using valarray and apply scale
    const std::string name_a = "indices.npy", name_b = "indptr.npy", name_c = "shape.npy",
                      name_d = "data.npy", name_e = "format.npy";
    std::vector<double>* value_vec = new std::vector<double>[num_spots];
    std::vector<mqi::key_t>* vox_vec = new std::vector<mqi::key_t>[num_spots];
    std::vector<double> data_vec;
    std::vector<uint32_t> indices_vec;
    std::vector<uint32_t> indptr_vec;
    mqi::key_t vox_ind, spot_ind;
    double value;
    int spot_start = 0, spot_end = 0;
    int vox_in_spot[num_spots];
    std::vector<double>::iterator it_data;
    std::vector<uint32_t>::iterator it_ind;
    std::vector<mqi::key_t>::iterator it_spot;
    int vox_count;
    printf("save_to_npz\n");

    printf("scan start %d\n", src->max_capacity_);
    for (int ind = 0; ind < src->max_capacity_; ind++) {
        if (src->data_[ind].key1 != mqi::empty_pair && src->data_[ind].key2 != mqi::empty_pair) {
            vox_count = 0;
            vox_ind = src->data_[ind].key1;
            spot_ind = src->data_[ind].key2;
            assert(vox_ind >= 0 && vox_ind < vol_size);
            value = src->data_[ind].value;
            value_vec[spot_ind].push_back(value * scale);
            vox_vec[spot_ind].push_back(vox_ind);
        }
    }

    vox_count = 0;
    indptr_vec.push_back(vox_count);
    for (int ii = 0; ii < num_spots; ii++) {
        data_vec.insert(data_vec.end(), value_vec[ii].begin(), value_vec[ii].end());
        indices_vec.insert(indices_vec.end(), vox_vec[ii].begin(), vox_vec[ii].end());
        vox_count += vox_vec[ii].size();
        indptr_vec.push_back(vox_count);
    }

    printf("scan done %lu %lu %lu\n", data_vec.size(), indices_vec.size(), indptr_vec.size());
    printf("%d %d\n", vol_size, num_spots);

    uint32_t shape[2] = {num_spots, vol_size};
    std::string format = "csr";
    size_t size_a = indices_vec.size(), size_b = indptr_vec.size(), size_c = 2,
           size_d = data_vec.size(), size_e = 3;

    uint32_t* indices = new uint32_t[indices_vec.size()];
    uint32_t* indptr = new uint32_t[indptr_vec.size()];
    double* data = new double[data_vec.size()];
    std::copy(indices_vec.begin(), indices_vec.end(), indices);
    std::copy(indptr_vec.begin(), indptr_vec.end(), indptr);
    std::copy(data_vec.begin(), data_vec.end(), data);
    printf("%lu\n", size_b);
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_a, indices, size_a, "w");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_b, indptr, size_b, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_c, shape, size_c, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_d, data, size_d, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_e, format, size_e, "a");
}

template <typename R>
void mqi::io::save_to_npz2(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                           const std::string& filename, mqi::vec3<mqi::ijk_t> dim,
                           uint32_t num_spots) {
    uint32_t vol_size;
    vol_size = src->roi_->get_mask_size();
    /// create a copy using valarray and apply scale
    const std::string name_a = "indices.npy", name_b = "indptr.npy", name_c = "shape.npy",
                      name_d = "data.npy", name_e = "format.npy";

    std::vector<double>* value_vec = new std::vector<double>[vol_size];
    std::vector<mqi::key_t>* spot_vec = new std::vector<mqi::key_t>[vol_size];
    std::vector<double> data_vec;
    std::vector<uint32_t> indices_vec;
    std::vector<uint32_t> indptr_vec;
    mqi::key_t vox_ind, spot_ind;
    double value;
    int spot_start = 0, spot_end = 0;
    std::vector<double>::iterator it_data;
    std::vector<uint32_t>::iterator it_ind;
    std::vector<mqi::key_t>::iterator it_spot;
    int spot_count;
    printf("save_to_npz\n");

    printf("scan start %d\n", src->max_capacity_);
    for (int ind = 0; ind < src->max_capacity_; ind++) {
        if (src->data_[ind].key1 != mqi::empty_pair && src->data_[ind].key2 != mqi::empty_pair) {
            vox_ind = src->data_[ind].key1;
            vox_ind = src->roi_->get_mask_idx(vox_ind);
            if (vox_ind < 0) {
                printf("is this right?\n");
                continue;
            }
            spot_ind = src->data_[ind].key2;
            assert(vox_ind >= 0 && vox_ind < vol_size);
            value = src->data_[ind].value;
            assert(value > 0);
            value_vec[vox_ind].push_back(value * scale);
            spot_vec[vox_ind].push_back(spot_ind);
        }
    }
    printf("Sorting start\n");
    for (int ind = 0; ind < vol_size; ind++) {
        if (spot_vec[ind].size() > 1) {
            std::vector<int> sort_ind(spot_vec[ind].size());
            std::iota(sort_ind.begin(), sort_ind.end(), 0);
            sort(sort_ind.begin(), sort_ind.end(),
                 [&](int i, int j) { return spot_vec[ind][i] < spot_vec[ind][j]; });
            std::vector<double> sorted_value(spot_vec[ind].size());
            std::vector<mqi::key_t> sorted_spot(spot_vec[ind].size());
            for (int sorted_ind = 0; sorted_ind < spot_vec[ind].size(); sorted_ind++) {
                sorted_value[sorted_ind] = value_vec[ind][sort_ind[sorted_ind]];
                sorted_spot[sorted_ind] = spot_vec[ind][sort_ind[sorted_ind]];
            }
            spot_vec[ind] = sorted_spot;
            value_vec[ind] = sorted_value;
        }
    }

    spot_count = 0;
    indptr_vec.push_back(spot_count);
    for (int ii = 0; ii < vol_size; ii++) {
        data_vec.insert(data_vec.end(), value_vec[ii].begin(), value_vec[ii].end());
        indices_vec.insert(indices_vec.end(), spot_vec[ii].begin(), spot_vec[ii].end());
        spot_count += spot_vec[ii].size();
        indptr_vec.push_back(spot_count);
    }

    uint32_t shape[2] = {vol_size, num_spots};
    std::string format = "csr";
    size_t size_a = indices_vec.size(), size_b = indptr_vec.size(), size_c = 2,
           size_d = data_vec.size(), size_e = 3;

    uint32_t* indices = new uint32_t[indices_vec.size()];
    uint32_t* indptr = new uint32_t[indptr_vec.size()];
    double* data = new double[data_vec.size()];
    std::copy(indices_vec.begin(), indices_vec.end(), indices);
    std::copy(indptr_vec.begin(), indptr_vec.end(), indptr);
    std::copy(data_vec.begin(), data_vec.end(), data);
    printf("%lu\n", size_b);
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_a, indices, size_a, "w");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_b, indptr, size_b, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_c, shape, size_c, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_d, data, size_d, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_e, format, size_e, "a");
}

template <typename R>
void mqi::io::save_to_npz(const mqi::scorer<R>* src, const R scale, const std::string& filepath,
                          const std::string& filename, mqi::vec3<mqi::ijk_t> dim,
                          uint32_t num_spots, R* time_scale, R threshold) {
    uint32_t vol_size;
    vol_size = dim.x * dim.y * dim.z;
    /// create a copy using valarray and apply scale
    const std::string name_a = "indices.npy", name_b = "indptr.npy", name_c = "shape.npy",
                      name_d = "data.npy", name_e = "format.npy";
    std::vector<double> value_vec[num_spots];
    std::vector<mqi::key_t> vox_vec[num_spots];
    std::vector<double> data_vec;
    std::vector<uint32_t> indices_vec;
    std::vector<uint32_t> indptr_vec;
    mqi::key_t vox_ind, spot_ind;
    double value;
    int spot_start = 0, spot_end = 0;
    int vox_in_spot[num_spots];
    std::vector<double>::iterator it_data;
    std::vector<uint32_t>::iterator it_ind;
    std::vector<mqi::key_t>::iterator it_spot;
    int vox_count;
    printf("save_to_npz\n");
    for (int ind = 0; ind < num_spots; ind++) {
        vox_in_spot[ind] = 0;
    }
    printf("scan start %d\n", src->max_capacity_);
    for (int ind = 0; ind < src->max_capacity_; ind++) {
        if (src->data_[ind].key1 != mqi::empty_pair && src->data_[ind].key2 != mqi::empty_pair) {
            vox_count = 0;
            vox_ind = src->data_[ind].key1;
            spot_ind = src->data_[ind].key2;
            assert(vox_ind >= 0 && vox_ind < vol_size);
            value = src->data_[ind].value;
            value *= scale;
            value -= 2 * threshold;
            if (value < 0)
                value = 0;
            value /= time_scale[spot_ind];
            value_vec[spot_ind].push_back(value);
            vox_vec[spot_ind].push_back(vox_ind);
        }
    }

    vox_count = 0;
    indptr_vec.push_back(vox_count);
    for (int ii = 0; ii < num_spots; ii++) {
        data_vec.insert(data_vec.end(), value_vec[ii].begin(), value_vec[ii].end());
        indices_vec.insert(indices_vec.end(), vox_vec[ii].begin(), vox_vec[ii].end());
        vox_count += vox_vec[ii].size();
        indptr_vec.push_back(vox_count);
    }
    printf("scan done %lu %lu %lu\n", data_vec.size(), indices_vec.size(), indptr_vec.size());
    printf("%d %d\n", vol_size, num_spots);

    uint32_t shape[2] = {num_spots, vol_size};
    std::string format = "csr";
    size_t size_a = indices_vec.size(), size_b = indptr_vec.size(), size_c = 2,
           size_d = data_vec.size(), size_e = 3;

    uint32_t* indices = new uint32_t[indices_vec.size()];
    uint32_t* indptr = new uint32_t[indptr_vec.size()];
    double* data = new double[data_vec.size()];
    std::copy(indices_vec.begin(), indices_vec.end(), indices);
    std::copy(indptr_vec.begin(), indptr_vec.end(), indptr);
    std::copy(data_vec.begin(), data_vec.end(), data);
    printf("%lu\n", size_b);
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_a, indices, size_a, "w");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_b, indptr, size_b, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_c, shape, size_c, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_d, data, size_d, "a");
    mqi::io::save_npz(filepath + "/" + filename + ".npz", name_e, format, size_e, "a");
}

template <typename R>
void mqi::io::save_to_mhd(const mqi::node_t<R>* children, const double* src, const R scale,
                          const std::string& filepath, const std::string& filename,
                          const uint32_t length) {
    ///< TODO: this works only for two depth world
    ///< TODO: dx, dy, and dz calculation works only for AABB
    float dx = children->geo[0].get_x_edges()[1];
    dx -= children->geo[0].get_x_edges()[0];
    float dy = children->geo[0].get_y_edges()[1];
    dy -= children->geo[0].get_y_edges()[0];
    float dz = children->geo[0].get_z_edges()[1];
    dz -= children->geo[0].get_z_edges()[0];
    float x0 = children->geo[0].get_x_edges()[0];
    x0 += children->geo[0].get_x_edges()[0];
    x0 /= 2.0;
    float y0 = children->geo[0].get_y_edges()[0];
    y0 += children->geo[0].get_y_edges()[0];
    y0 /= 2.0;
    float z0 = children->geo[0].get_z_edges()[0];
    z0 += children->geo[0].get_z_edges()[0];
    z0 /= 2.0;
    std::ofstream fid_header(filepath + "/" + filename + ".mhd", std::ios::out);
    if (!fid_header) {
        std::cout << "Cannot open file!" << std::endl;
    }
    fid_header << "ObjectType = Image\n";
    fid_header << "NDims = 3\n";
    fid_header << "BinaryData = True\n";
    fid_header
        << "BinaryDataByteOrderMSB = False\n";  // True for big endian, False for little endian
    fid_header << "CompressedData = False\n";
    fid_header << "TransformMatrix 1 0 0 0 1 0 0 0 1\n";
    fid_header << "Offset " << x0 << " " << y0 << " " << z0 << std::endl;
    fid_header << "CenterOfRotation 0 0 0\n";
    fid_header << "AnatomicOrientation = RAI\n";
    fid_header << "DimSize = " << children->geo[0].get_nxyz().x << " "
               << children->geo[0].get_nxyz().y << " " << children->geo[0].get_nxyz().z << "\n";
    ///< TODO: if R is double, MET_FLOAT should be MET_DOUBLE
    fid_header << "ElementType = MET_DOUBLE\n";

    fid_header << "ElementSpacing = " << dx << " " << dy << " " << dz << "\n";
    fid_header << "ElementDataFile = " << filename << ".raw"
               << "\n";
    fid_header.close();
    if (!fid_header.good()) {
        std::cout << "Error occurred at writing time!" << std::endl;
    }
    std::valarray<double> dest(src, length);
    munmap(&dest, length * sizeof(double));
    dest *= scale;
    std::ofstream fid_raw(filepath + "/" + filename + ".raw", std::ios::out | std::ios::binary);
    if (!fid_raw) {
        std::cout << "Cannot open file!" << std::endl;
    }
    fid_raw.write(reinterpret_cast<const char*>(&dest[0]), length * sizeof(double));

    fid_raw.close();
    if (!fid_raw.good()) {
        std::cout << "Error occurred at writing time!" << std::endl;
    }
}

template <typename R>
void mqi::io::save_to_mha(const mqi::node_t<R>* children, const double* src, const R scale,
                          const std::string& filepath, const std::string& filename,
                          const uint32_t length) {
    ///< TODO: this works only for two depth world
    ///< TODO: dx, dy, and dz calculation works only for AABB
    float dx = children->geo[0].get_x_edges()[1];
    dx -= children->geo[0].get_x_edges()[0];
    float dy = children->geo[0].get_y_edges()[1];
    dy -= children->geo[0].get_y_edges()[0];
    float dz = children->geo[0].get_z_edges()[1];
    dz -= children->geo[0].get_z_edges()[0];
    float x0 = children->geo[0].get_x_edges()[0] + dx * 0.5;
    float y0 = children->geo[0].get_y_edges()[0] + dy * 0.5;
    float z0 = children->geo[0].get_z_edges()[0] + dz * 0.5;
    std::cout << "x0 " << std::setprecision(9) << x0 << " y0 " << y0 << " z0 " << z0 << std::endl;
    std::valarray<double> dest(src, length);
    munmap(&dest, length * sizeof(double));
    dest *= scale;
    std::ofstream fid_header(filepath + "/" + filename + ".mha", std::ios::out);
    if (!fid_header) {
        std::cout << "Cannot open file!" << std::endl;
    }
    fid_header << "ObjectType = Image\n";
    fid_header << "NDims = 3\n";
    fid_header << "BinaryData = True\n";
    fid_header
        << "BinaryDataByteOrderMSB = False\n";  // True for big endian, False for little endian
    fid_header << "CompressedData = False\n";
    fid_header << "TransformMatrix = 1 0 0 0 1 0 0 0 1\n";
    fid_header << "Origin = " << std::setprecision(9) << x0 << " " << y0 << " " << z0 << "\n";
    fid_header << "CenterOfRotation = 0 0 0\n";
    fid_header << "AnatomicOrientation = RAI\n";
    fid_header << "DimSize = " << children->geo[0].get_nxyz().x << " "
               << children->geo[0].get_nxyz().y << " " << children->geo[0].get_nxyz().z << "\n";
    ///< TODO: if R is double, MET_FLOAT should be MET_DOUBLE
    fid_header << "ElementType = MET_DOUBLE\n";
    fid_header << "HeaderSize = -1\n";
    fid_header << "ElementSpacing = " << std::setprecision(9) << dx << " " << dy << " " << dz
               << "\n";
    fid_header << "ElementDataFile = LOCAL\n";
    fid_header.write(reinterpret_cast<const char*>(&dest[0]), length * sizeof(double));
    fid_header.close();
    if (!fid_header.good()) {
        std::cout << "Error occurred at writing time!" << std::endl;
    }
}

template <typename R>
void mqi::io::save_to_dcm(const mqi::node_t<R>* children, const double* src, const R scale,
                          const std::string& filepath, const std::string& filename,
                          const uint32_t length, bool twoCentimeterMode) {
    ///< Implementation of DICOM RT Dose file saving using DCMTK
    ///< Supports both 2D (TwoCentimeterMode) and 3D dose distributions

    // Calculate voxel dimensions from geometry
    float dx = children->geo[0].get_x_edges()[1] - children->geo[0].get_x_edges()[0];
    float dy = children->geo[0].get_y_edges()[1] - children->geo[0].get_y_edges()[0];
    float dz = children->geo[0].get_z_edges()[1] - children->geo[0].get_z_edges()[0];

    // Calculate image position (origin) - center of first voxel
    float x0 = children->geo[0].get_x_edges()[0] + dx * 0.5;
    float y0 = children->geo[0].get_y_edges()[0] + dy * 0.5;
    float z0 = children->geo[0].get_z_edges()[0] + dz * 0.5;

    // Get dimensions from geometry
    uint32_t nx = children->geo[0].get_nxyz().x;
    uint32_t ny = children->geo[0].get_nxyz().y;
    uint32_t nz = children->geo[0].get_nxyz().z;

    // For 2D mode (TwoCentimeterMode), we only save the scoring slice at 2cm depth
    if (twoCentimeterMode) {
        nz = 1;  // Only one slice for 2D dose
        // Adjust z0 to be at the 2cm depth position
        z0 = 20.0;  // 2cm in mm (DICOM uses mm units)
    }

    // Create a copy of data and apply scale
    std::valarray<double> dose_data(src, length);
    dose_data *= scale;

    // Create DICOM file format
    DcmFileFormat fileformat;
    DcmDataset* dataset = fileformat.getDataset();

    // Basic DICOM attributes
    dataset->putAndInsertString(DCM_SOPClassUID, UID_RTDOSEStorage);
    dataset->putAndInsertString(DCM_SOPInstanceUID,
                                "1.2.3.4.5.6.7.8.9.0.1");  // TODO: Generate unique UID
    dataset->putAndInsertString(DCM_PatientName, "MOQUI_PATIENT");
    dataset->putAndInsertString(DCM_PatientID, "MOQUI_001");
    dataset->putAndInsertString(DCM_Modality, "RTDOSE");
    dataset->putAndInsertString(DCM_Manufacturer, "Moqui Monte Carlo");

    // Image information
    dataset->putAndInsertUint16(DCM_Columns, nx);
    dataset->putAndInsertUint16(DCM_Rows, ny);
    dataset->putAndInsertUint16(DCM_NumberOfFrames, nz);

    // Pixel spacing (in mm)
    char pixelSpacing[64];
    snprintf(pixelSpacing, sizeof(pixelSpacing), "%.6f\%.6f", dx, dy);
    dataset->putAndInsertString(DCM_PixelSpacing, pixelSpacing);

    // Slice thickness (in mm)
    char sliceThickness[32];
    snprintf(sliceThickness, sizeof(sliceThickness), "%.6f", dz);
    dataset->putAndInsertString(DCM_SliceThickness, sliceThickness);

    // Image position and orientation
    char imagePosition[128];
    if (twoCentimeterMode) {
        snprintf(imagePosition, sizeof(imagePosition), "%.6f\%.6f\%.6f", x0, y0, z0);
    } else {
        snprintf(imagePosition, sizeof(imagePosition), "%.6f\%.6f\%.6f", x0, y0, z0);
    }
    dataset->putAndInsertString(DCM_ImagePositionPatient, imagePosition);

    // Image orientation (patient) - standard axial orientation
    dataset->putAndInsertString(DCM_ImageOrientationPatient, "1\0\0\0\1\0");

    // Dose units and scaling
    dataset->putAndInsertString(DCM_DoseUnits, "GY");
    dataset->putAndInsertString(DCM_DoseType, "PHYSICAL");
    dataset->putAndInsertString(DCM_DoseSummationType, "PLAN");

    // Dose scaling
    double doseGridScaling = 1.0;  // Apply appropriate scaling factor
    dataset->putAndInsertFloat64(DCM_DoseGridScaling, doseGridScaling);

    // Pixel data
    Uint16* pixelData = new Uint16[nx * ny * nz];

    // Convert dose data to 16-bit integer format
    double maxDose = 0.0;
    for (size_t i = 0; i < dose_data.size(); ++i) {
        if (dose_data[i] > maxDose) {
            maxDose = dose_data[i];
        }
    }

    // Scale to 16-bit range
    if (maxDose > 0.0) {
        double scaleFactor = 65535.0 / maxDose;
        for (size_t i = 0; i < dose_data.size(); ++i) {
            pixelData[i] = static_cast<Uint16>(dose_data[i] * scaleFactor);
        }
    }

    // Set pixel data attributes
    dataset->putAndInsertUint16(DCM_BitsAllocated, 16);
    dataset->putAndInsertUint16(DCM_BitsStored, 16);
    dataset->putAndInsertUint16(DCM_HighBit, 15);
    dataset->putAndInsertUint16(DCM_PixelRepresentation, 0);  // Unsigned integer
    dataset->putAndInsertUint16(DCM_SamplesPerPixel, 1);
    dataset->putAndInsertString(DCM_PhotometricInterpretation, "MONOCHROME2");

    // Insert pixel data
    OFCondition cond = dataset->putAndInsertUint16Array(DCM_PixelData, pixelData, nx * ny * nz);

    if (cond.bad()) {
        std::cout << "Error: Could not insert pixel data: " << cond.text() << std::endl;
        delete[] pixelData;
        return;
    }

    // Save the DICOM file
    OFString filename_dcm = (filepath + "/" + filename + ".dcm").c_str();
    cond = fileformat.saveFile(filename_dcm, EXS_LittleEndianExplicit);

    if (cond.bad()) {
        std::cout << "Error: Could not save DICOM file: " << cond.text() << std::endl;
    } else {
        std::cout << "Successfully saved DICOM file: " << filename_dcm << std::endl;
        if (twoCentimeterMode) {
            std::cout << "Mode: 2D dose (TwoCentimeterMode) - 1 frame at 2cm depth" << std::endl;
        } else {
            std::cout << "Mode: 3D dose - " << nz << " frames" << std::endl;
        }
    }

    // Clean up
    delete[] pixelData;
}

#endif
