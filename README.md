# ĐỒ ÁN QUẢN LÝ CHUYẾN BAY

# Table of Contents
- [ĐỀ BÀI](#1)
- [CHỨC NĂNG](#2)
- [LƯU Ý](#3)
- [THẦY NHẬN XÉT](#4)

 
## ĐỀ BÀI <a name="1"></a>

#### Máy bay: 
+ Mảng con trỏ có tối đa 300 máy bay. 
+ Mỗi máy bay có các thông tin (Số hiệu MB (C15), loại máy bay (C40), số chỗ)
+ Mỗi máy bay có 1 số hiệu duy nhất; số chỗ >=20

#### Chuyến bay: 
+ Danh sách liên kết đơn (Mã CB: C15, Ngày giờ khởi hành, Sân bay đến, Trạng thái, Số hiệu MB, danh sách vé). 
+ Mỗi chuyến bay có 1 mã duy nhất
+ Trạng thái chuyến bay bao gồm: 0: hủy chuyến, 1: còn vé, 2: hết vé, 3: hoàn tất
+ Danh sách vé cho biết thông tin vé trên chuyến bay, và số CMND của hành khách đã đặt vé đó. (mảng con trỏ)
+ Mỗi vé có số vé là số thứ tự trên chuyến từ số 1 đến số chỗ. Danh sách vé được cấp phát bộ nhớ tự động dựa vào số chỗ của máy bay thực hiện chuyến bay.

#### Hành khách: 
+ Cây nhị phân tìm kiếm cân bằng (Số CMND, Ho, Ten, Phai)

#### Chương trình có các chức năng sau: 

a/ Cập nhập danh sách các máy bay (thêm / xóa / hiệu chỉnh)      -         

b/ Cập nhật chuyến bay: cho phép lập chuyến bay mới, hiệu chỉnh ngày giờ khởi hành của chuyến bay, hủy chuyến.

c/ Đặt vé: cho phép đặt vé trên 1 chuyến bay; nếu thông tin hành khách chưa có thì tự động cập nhật vào danh sách hành khách, nếu có rồi thì in ra màn hình để kiểm tra. Mỗi vé đều phải ghi nhận số CMND của hành khách; nếu hành khách chưa có số CMND thì yêu cầu nhập thông tin hành khách trước. Trên 1 chuyến bay, mỗi hành khách chỉ được mua 1 vé. 

d/ Hủy vé: cho phép hủy vé đã đặt của hành khách.

e/ In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay. Kết xuất:

DANH SÁCH HÀNH KHÁCH THUỘC CHUYẾN BAY ######
Ngày giờ khởi hành:   dd/mm/yyyy    hh:mm    Nơi đến: xxxxxxxxxxx

	STT	SỐ VÉ		SỐ CMND	HỌ TÊN	PHÁI


f/ In danh sách các chuyến bay khởi hành trong ngày dd/mm/yyyy đến nơi XXXX (cho biết cụ thể số lượng các vé còn trống và giờ khởi hành) 

g/ In danh sách các vé còn trống của 1 chuyến bay có mã chuyến bay là X. 
h/ Thống kê số lượt thực hiện chuyến bay của từng máy bay theo thứ tự số lượt thực hiện giảm dần. Kết xuất:
	Số hiệu máy bay		Số lượt thực hiện chuyến bay

Lưu ý: Chương trình cho phép lưu các danh sách vào file; Kiểm tra các điều kiện khi nhập liệu làm dữ liệu bị sai.


## CHỨC NĂNG <a name="2"></a>

a) MÁY BAY (thêm, xóa, hiệu chỉnh)

- Thêm (id trùng, trống 1 trong 3 trường, khoảng trắng ở số loại, id plane phải viết hoa, số chỗ 20 - 300)
- Xóa ( Khi chưa thành lập chuyến bay)
- Chỉnh sửa:
    - Chưa thành lập chuyến bay: Sửa type và seats
    - Đã thành lập nhưng status là còn vé hoặc hết vé → chỉ cho sửa số ghế tăng dần
        (cập nhật chuyến bay số ghế tăng dần)
        
b) CHUYẾN BAY (thêm,cancle,hiệu chỉnh ngày giờ)

Danh sách tự cập nhật sold out, completed(nếu ko có ai đặt vé trả về trạng thái hủy)

- Thêm (id flight trùng, id plane không tồn tại, ngày giờ hợp lệ, thời gian ≥ 1 h từ hiện tại,khác id flight trùng id plane ≥ 12 hour từ chuyến bay đó)
- Hiệu chỉnh (chuyến còn vé hoặc hết vé , bắt lỗi thời gian nếu có hành khách khác 1 người, hiệu chỉnh từ mốc thời gian hiện tại tăng lên 1 tiếng,  không cho hiệu chỉnh trong 30 phút cuối, nếu hiệu chỉnh vào phút 29 thì kiểm tra nếu qua phút 30 thì tự động thoát ra màn hình chính, nếu hiệu chỉnh vào lúc chuyến bay đã hoàn thành thì thoát ra)
- Hủy (còn vé hoặc hết vé )

c) ĐẶT VÉ(thêm hành khách)
- trống 1 trong 3 trường,chọn giới tính,màn hình đặt vé cho hành khách kiểm tra chuyến bay hoàn thành , < 30 phút khi lưu sẽ thoát về màn hình init ticket hoặc init menu
- ko cho đặt khách trong chuyến bay khác có time < 12 tiếng, hoặc cùng ID trong chuyến bay , nếu có xóa dữ liệu edittext ID

d) HỦY VÉ
- Hủy vé khi chuyến bay chưa hoàn thành chưa cancle, chưa tới 30 phút cuối trước khi bay

e/ In danh sách các hành khách thuộc 1 chuyến bay dựa vào mã chuyến bay
- In theo kiểu prefix

h/ Thống kê số lượt thực hiện chuyến bay của từng máy bay
- Tạo một mảng mới lưu vị trí, và sắp xếp vị trí trên mảng đó ko làm ảnh hưởng đến danh sách máy bay



## LƯU Ý <a name="3"></a>
- Đối với con trỏ sử dụng toán tử `new` phải giải phóng vùng nhớ, đặt biệt mảng con trỏ
- Chú ý làm kĩ các file `CTDL`
- Chú ý các khi nhập id thì phải viết hoa không khoảng trắng, họ tên thì viết hoa chữ cái đầu VD `Ngoc Anh`
- Chú ý bắt các lỗi về thời gian

## THẦY NHẬN XÉT <a name="4"></a>
- Khen
  - Chức năng lọc chuyến bay
  - Sắp xếp dsmb không làm ảnh hưởng đến danh sách gốc

- Chê
  - Trường nơi đến phải viết hoa chữ cái đầu
  - Chưa có chức năng xem toàn bộ danh sách hành khách và chỉnh sửa
  - Danh sách vé khi nào có người đặt mới cấp phát bộ nhớ 

- Câu hỏi phụ
  - Cho một danh sách gồm 30000 phần tử trong đó chứa dữ liệu từ [1-32000] hỏi làm sao để load vào bộ nhớ tối ưu nhất và sắp xếp nhanh nhất
 
