# Vườn Thông Minh

## Giới Thiệu

Vườn Thông Minh là một dự án có mục tiêu tạo ra một hệ thống tự động hóa quản lý và chăm sóc cho vườn cây của bạn. Ứng dụng này sử dụng các công nghệ để giúp người dùng theo dõi và điều khiển các thành phần của vườn, bao gồm cả việc tưới nước, điều khiển mái che, theo dõi độ ẩm đất, ánh sáng, nhiệt độ.

## Mục Tiêu Dự Án

Dự án "Vườn Thông Minh" được thiết kế để cung cấp giải pháp tự động hóa cho việc quản lý và chăm sóc cây trong vườn. Hệ thống sử dụng các công nghệ như ESP32, cảm biến độ ẩm đất, cảm biến ánh sáng, DHT11, cảm biến chuyển động và mái che điều khiển.

## Chức Năng Chính

### 1. Tưới Nước Tự Động

Hệ thống có khả năng tưới nước tự động dựa trên dữ liệu độ ẩm của đất. Người dùng cũng có thể quyết định điều khiển việc tưới nước.

### 2. Theo Dõi Độ Ẩm Đất

Cảm biến độ ẩm đất liên tục theo dõi điều kiện đất, cung cấp thông tin chi tiết về mức độ ẩm để người dùng có thể điều chỉnh chăm sóc.

### 3. Kiểm Soát Ánh Sáng

Hệ thống có khả năng theo dõi và điều chỉnh ánh sáng tự nhiên hoặc nhân tạo để tối ưu hóa điều kiện phát triển của cây.

### 4. Theo Dõi Nhiệt Độ

Hệ thống có khả năng theo dõi nhiệt độ và điều chỉnh môi trường khi nhiệt độ ảnh hưởng khả năng phát triển của cây.

### 5. Điều Khiển Mái Che

Tự động điều khiển mái che theo các điều kiện ngoại cảnh và thời gian.

### 6. Giao Diện Người Dùng Thân Thiện

Ứng dụng cung cấp một giao diện người dùng dễ sử dụng, cho phép người dùng theo dõi và điều khiển vườn của họ từ xa qua ứng dụng IoT cloud là Blynk.

## Thành Phần Chính:

- ESP32 và Blynk: ESP32 được sử dụng làm trung tâm điều khiển, kết nối với Blynk để cung cấp giao diện người dùng và điều khiển từ xa.
- Cảm Biến Độ Ẩm Đất: Cảm biến độ ẩm đất giúp theo dõi mức độ ẩm trong đất. Dữ liệu được hiển thị trên Blynk và LCD.
- Cảm Biến Nhiệt Độ(DHT11): Theo dõi nhiệt độ môi trường. Dữ liệu sử dụng để tính toán, hiển thị trên Blynk và LCD.
- Cảm Biến Ánh Sáng: Cảm biến ánh sáng đo lường cường độ ánh sáng môi trường. Dữ liệu được truyền lên Blynk và hiển thị trên LCD.
- Cảm Biến Chuyển Động: Cảm biến chuyển động đếm số lần phát hiện chuyển động trong ngày. Thông tin được gửi đến Blynk.
- Mái Che Tự Động: Kiểm soát mái che dựa trên điều kiện thời tiết và môi trường. Tự động mở vào buổi sáng, đóng vào buổi tối và điều chỉnh khi có nhiệt độ cao.

## Cách Hoạt Động:

### Đọc Dữ Liệu:

Các cảm biến đọc dữ liệu về độ ẩm đất, ánh sáng và nhiệt độ.
Cảm biến chuyển động đếm số lần phát hiện.

### Kiểm Soát Mái Che:

Dựa trên dữ liệu đọc được và thời gian, mái che được điều chỉnh tự động để bảo vệ cây.

### Quản Lý Tưới Nước:

Tưới nước tự động khi độ ẩm đất thấp hoặc khi người dùng chỉ định.

### Hiển Thị Dữ Liệu:

Dữ liệu độ ẩm đất, ánh sáng, nhiệt độ và số lần phát hiện chuyển động được hiển thị trên LCD và Blynk.

## Tác Giả:

Võ Long (@longvo92)
Email: vtlong29@gmail.com
