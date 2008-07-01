#ifndef AWS_S3RESPONSE_API_H
#define AWS_S3RESPONSE_API_H

#include <vector>
#include <string>
#include <libaws/common.h>

namespace aws {

  // forward declaration of internal response classes
  namespace s3 {
      class CreateBucketResponse;
      class ListAllBucketsResponse;
      class DeleteBucketResponse;
      class ListBucketResponse;
      class PutResponse;
      class GetResponse;
      class HeadResponse;
      class DeleteResponse;
  } /* namespace s3 */

  /** \brief S3Response is the base class of all classes that can be
   *         returned as a result of a S3 request.
   */
  template <class T>
  class S3Response : public SmartObject
  {
    public:
      virtual ~S3Response();

      virtual const std::string&
      getRequestId() const;
      
      virtual const std::string&
      getETag() const;
      
      virtual const std::string&
      getDate() const;
      
      virtual const std::string&
      getAmazonId() const;

    protected:
      T* theS3Response;
      S3Response(T*);

  }; /* class S3Response */

  class CreateBucketResponse : public S3Response<s3::CreateBucketResponse>
  {
    public:
      virtual ~CreateBucketResponse() {}

      /** \brief The name of the bucket that was created.
       */
	    virtual const std::string& 
      getBucketName() const;
      
      virtual const std::string& 
      getLocation() const;

    private:
      friend class S3ConnectionImpl;
      CreateBucketResponse(s3::CreateBucketResponse*);
  }; /* class CreateBucketResponse */

  class ListAllBucketsResponse : public S3Response<s3::ListAllBucketsResponse>
  {
    public:
      struct Bucket {
        std::string BucketName;
        std::string CreationDate;
      };

      virtual ~ListAllBucketsResponse() {}

      virtual void
      open() const;

      virtual bool
      next(Bucket&) const;

      virtual void
      close() const;

      virtual const std::string& 
      getOwnerId() const;

      virtual const std::string&
      getOwnerDisplayName() const;

    private:
      friend class S3ConnectionImpl;
      ListAllBucketsResponse(s3::ListAllBucketsResponse*);
  }; /* class ListAllBucketsResponse */

  class DeleteBucketResponse  : public S3Response<s3::DeleteBucketResponse>
  {
    public:
      DeleteBucketResponse(s3::DeleteBucketResponse*);
      virtual ~DeleteBucketResponse() {}

      virtual const std::string&
      getBucketName() const;
    private:
      friend class S3ConnectionImpl;
  }; /* class DeleteBucketResponse */


  class ListBucketResponse  : public S3Response<s3::ListBucketResponse>
  {
    public:
      struct Object {
        std::string KeyValue;
        std::string LastModified;
        std::string ETag;
        size_t      Size;
      };

      ListBucketResponse(s3::ListBucketResponse*);
      virtual ~ListBucketResponse() {}

      virtual void
      open() const;

      virtual bool
      next(Object&) const;

      virtual void
      close() const;

      virtual const std::string&
      getBucketName() const;

      virtual const std::string&
      getPrefix() const;

      virtual const std::string&
      getMarker() const;

      virtual const std::string&
      getDelimiter() const;

      virtual const std::vector<std::string>&
      getCommonPrefixes() const;

      virtual int
      getMaxKeys() const;

      virtual bool
      isTruncated() const;

    private:
      friend class S3ConnectionImpl;
  }; /* class ListBucketsResponse */

  class PutResponse  : public S3Response<s3::PutResponse>
  {
    public:
      virtual ~PutResponse() {}

      virtual const std::string& 
      getBucketName() const;

    private:
      friend class S3ConnectionImpl;
      PutResponse(s3::PutResponse*);
  }; /* class PutResponse */

  class GetResponse  : public S3Response<s3::GetResponse>
  {
    public:
      virtual ~GetResponse() {}

      virtual const std::string&
      getKey() const;

      virtual const std::string&
      getBucketName() const;

      virtual std::istream&
      getInputStream() const;

    private:
      friend class S3ConnectionImpl;
      GetResponse(s3::GetResponse*);
  }; /* class GetResponse */

  class HeadResponse  : public S3Response<s3::HeadResponse>
  {
    public:
      virtual ~HeadResponse() {}

      virtual const std::string&
      getBucketName() const;

    private:
      friend class S3ConnectionImpl;
      HeadResponse(s3::HeadResponse*);
  }; /* class HeadResponse */

  class DeleteResponse  : public S3Response<s3::DeleteResponse>
  {
    public:
      virtual ~DeleteResponse() {}

      virtual const std::string&
      getKey() const;

      virtual const std::string&
      getBucketName() const;

    private:
      friend class S3ConnectionImpl;
      DeleteResponse(s3::DeleteResponse*);
  }; /* class DeleteResponse */

} /* namespace aws */
#endif
